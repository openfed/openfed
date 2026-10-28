<?php

namespace Drupal\partial_date;

/**
 * Description of DateTools.
 *
 * @author CosminFr
 */
class DateTools {

  /**
   * The minimum year that the module supports.
   *
   * Modifying this will alter how new timestamps are stored in the database.
   *
   * Setting to the something huge like 999999999999 should be OK, which would
   * be needed for things like the scienific age of the universe. +/- 2000 years
   * do not calculate leap years etc, and use a fixed number of seconds per year
   * based on the length of the tropical year in 2000.
   *
   * @var int
   */
  const YEAR_MIN = -999999999999;

  /**
   * The maximum year that the module supports.
   *
   * Modifying this will alter how new timestamps are stored in the database.
   *
   * @var int
   */
  const YEAR_MAX = 999999999999;

  /**
   * The number of seconds for a tropical year in 2000.
   *
   * Outside of the 1AD to 3999AD, leap years are ignored and a set number of
   * seconds per year are used to calculate the number seconds per year for the
   * timestamp estimations. This is a float column, so the percision of this
   * should be calculated to decide if this can be reduced even more.
   *
   * @var int
   */
  const SECONDS_PER_YEAR = 31556925;

  /**
   * Returns true, if given $year is a leap year.
   *
   * @param int $year
   *   The year to check.
   *
   * @return bool
   *   True, if year is leap year
   */
  public static function isLeapYear(int $year): bool {
    if (empty($year)) {
      return FALSE;
    }
    if ($year < 1582) {
      // Pre Gregorio XIII - 1582.
      return $year % 4 == 0;
    }
    else {
      // Post Gregorio XIII - 1582.
      return (($year % 4 == 0) && ($year % 100 != 0)) || ($year % 400 == 0);
    }
  }

  /**
   * Maps out the valid month ranges for a given year.
   *
   * @param int|null $year
   *   The year to check. If NULL, the current year is used.
   *
   * @return array
   *   Note, there is no array index.
   */
  public static function monthMatrix(?int $year = NULL): array {
    if ($year && static::isLeapYear($year)) {
      return [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
    }
    return [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
  }

  /**
   * Returns the last day of a given month.
   *
   * @param int $month
   *   The month to check.
   * @param int|null $year
   *   The year to check. If NULL, the current year is used.
   *
   * @return int
   *   The last day of the month.
   */
  public static function lastDayOfMonth(int $month, ?int $year = NULL): int {
    $matrix = self::monthMatrix($year);
    return $matrix[$month];
  }

  /**
   * Returns a translated array of month names.
   */
  public static function monthNames(?int $month = NULL) {
    static $month_names;
    if (empty($month_names)) {
      $month_names = [
        1 => t('January', [], ['context' => 'datetime']),
        2 => t('February', [], ['context' => 'datetime']),
        3 => t('March', [], ['context' => 'datetime']),
        4 => t('April', [], ['context' => 'datetime']),
        5 => t('May', [], ['context' => 'datetime']),
        6 => t('June', [], ['context' => 'datetime']),
        7 => t('July', [], ['context' => 'datetime']),
        8 => t('August', [], ['context' => 'datetime']),
        9 => t('September', [], ['context' => 'datetime']),
        10 => t('October', [], ['context' => 'datetime']),
        11 => t('November', [], ['context' => 'datetime']),
        12 => t('December', [], ['context' => 'datetime']),
      ];
    }
    if ($month) {
      return $month_names[$month];
    }
    return $month_names;
  }

  /**
   * Returns a translated array of short month names.
   */
  public static function monthAbbreviations($month) {
    static $month_names;
    if (empty($month_names)) {
      $month_names = [
        1 => t('Jan', [], ['context' => 'datetime']),
        2 => t('Feb', [], ['context' => 'datetime']),
        3 => t('Mar', [], ['context' => 'datetime']),
        4 => t('Apr', [], ['context' => 'datetime']),
        5 => t('May', [], ['context' => 'datetime']),
        6 => t('Jun', [], ['context' => 'datetime']),
        7 => t('Jul', [], ['context' => 'datetime']),
        8 => t('Aug', [], ['context' => 'datetime']),
        9 => t('Sep', [], ['context' => 'datetime']),
        10 => t('Oct', [], ['context' => 'datetime']),
        11 => t('Nov', [], ['context' => 'datetime']),
        12 => t('Dec', [], ['context' => 'datetime']),
      ];
    }
    if ($month) {
      return $month_names[$month];
    }
    return $month_names;
  }

  /**
   * Returns a translated array of weekday names.
   */
  public static function weekdayNames($week_day_number) {
    static $day_names;
    if (empty($day_names)) {
      $day_names = [
        0 => t('Sunday', [], ['context' => 'datetime']),
        1 => t('Monday', [], ['context' => 'datetime']),
        2 => t('Tuesday', [], ['context' => 'datetime']),
        3 => t('Wednesday', [], ['context' => 'datetime']),
        4 => t('Thursday', [], ['context' => 'datetime']),
        5 => t('Friday', [], ['context' => 'datetime']),
        6 => t('Saturday', [], ['context' => 'datetime']),
      ];
    }
    if ($week_day_number) {
      return $day_names[$week_day_number];
    }
    return $day_names;
  }

  /**
   * Returns a translated array of weekday names.
   */
  public static function weekdayAbbreviations($week_day_number, $length = 3) {
    $name = static::weekdayNames($week_day_number);
    if (mb_strlen($name) > $length) {
      return mb_substr($name, 0, $length);
    }
    return $name;
  }

  /**
   * Gets day of week, 0 = Sunday through 6 = Saturday.
   *
   * Pope Gregory removed 10 days - October 5 to October 14 - from the year 1582
   * and proclaimed that from that time onwards 3 days would be dropped from the
   * calendar every 400 years.
   *
   * Thursday, October 4, 1582 (Julian) was followed immediately by Friday,
   * October 15, 1582 (Gregorian).
   *
   * @see PEAR::Date_Calc
   */
  public static function dayOfWeek($year, $month, $day): float {
    $greg_correction = 0;
    if ($year < 1582 || ($year == 1582 && ($month < 10 || ($month == 10 && $day < 15)))) {
      $greg_correction = 3;
    }

    if ($month > 2) {
      $month -= 2;
    }
    else {
      $month += 10;
      $year--;
    }

    $result = floor((13 * $month - 1) / 5) +
           $day + ($year % 100) +
           floor(($year % 100) / 4) +
           floor(($year / 100) / 4) - 2 *
           floor($year / 100) + 77 + $greg_correction;

    return $result - 7 * floor($result / 7);
  }

  /**
   * Returns a translated ordinal suffix for a given day of the month.
   */
  public static function ordinalSuffix($day) {
    if (empty($day)) {
      return '';
    }
    static $suffixes;
    if (empty($suffixes)) {
      $suffixes = [
        'st' => t('st', [], ['context' => 'datetime']),
        'nd' => t('nd', [], ['context' => 'datetime']),
        'rd' => t('rd', [], ['context' => 'datetime']),
        'th' => t('th', [], ['context' => 'datetime']),
      ];
    }
    switch (($day = abs($day)) % 100) {
      case 11:
      case 12:
      case 13:
        return $suffixes['th'];

      default:
        switch ($day % 10) {
          case 1:
            return $suffixes['st'];

          case 2:
            return $suffixes['nd'];

          case 3:
            return $suffixes['rd'];

          default:
            return $suffixes['th'];
        }
    }
  }

}
