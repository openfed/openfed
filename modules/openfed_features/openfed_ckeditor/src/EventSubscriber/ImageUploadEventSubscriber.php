<?php

namespace Drupal\openfed_ckeditor\EventSubscriber;

use Drupal\Component\Utility\Html;
use Symfony\Component\EventDispatcher\EventSubscriberInterface;
use Symfony\Component\HttpFoundation\JsonResponse;
use Symfony\Component\HttpKernel\Event\ExceptionEvent;
use Symfony\Component\HttpKernel\Exception\UnprocessableEntityHttpException;
use Symfony\Component\HttpKernel\KernelEvents;

/**
 * Provides a subscriber to alter the image upload exception.
 */
class ImageUploadEventSubscriber implements EventSubscriberInterface {

  /**
   * Handles UnprocessableEntityHttpException for CKEditor5 image uploads.
   *
   * @param \Symfony\Component\HttpKernel\Event\ExceptionEvent $event
   *   The exception event.
   */
  public function onAccessDeniedException(ExceptionEvent $event): void {
    $exception = $event->getThrowable();

    // Only act on UnprocessableEntityHttpException exceptions.
    if (!$exception instanceof UnprocessableEntityHttpException) {
      return;
    }

    // Check if the route is the image upload route.
    $request = $event->getRequest();
    if ($request->attributes->get('_route') !== 'ckeditor5.upload_image') {
      return;
    }

    // Get the exception message from the throwable.
    $error_message = $exception->getMessage();

    // Remove the object type prefix if present.
    // e.g., "Object(Drupal\Core\Entity\Plugin\DataType\EntityAdapter): "
    $error_message = preg_replace('/^Object\([^)]+\):\s*/', '', $error_message);

    // Decode HTML entities and strip tags for plain text display in alert().
    $error_message = Html::decodeEntities($error_message);
    $error_message = strip_tags($error_message);

    $upload = $request->files->get('upload');

    // Create a JSON response in the format expected by drupalImage.js:
    // response.error.message
    $response = new JsonResponse([
      'error' => [
        'message' => sprintf("Couldn't upload file: %s\n%s", $upload->getClientOriginalName(), $error_message),
      ],
    ], 422);

    // Set the response to the event.
    $event->setResponse($response);
  }

  /**
   * Registers the methods in this class that should be listeners.
   *
   * @return array
   *   An array of event listener definitions.
   */
  public static function getSubscribedEvents(): array {
    $events[KernelEvents::EXCEPTION][] = ['onAccessDeniedException', 50];
    return $events;
  }

}
