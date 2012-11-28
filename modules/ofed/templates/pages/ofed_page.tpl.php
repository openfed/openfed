<div class="openfed-presentation">
  
  <?php echo $description; ?>

  <div class="listing">
    <?php $box = 1; ?>

    <?php foreach($list as $title => $elements) : ?>
      <?php if ($box == 1): ?>
        <div class="row">
      <?php endif; ?>
      <div class="box span-6">
        <h2><?php echo $title; ?></h2>
        <ul>
          <?php foreach( $elements as $infos) : ?>
            <li>
              <label>
                <?php echo $infos['name']; ?>
                <?php if ( isset($infos['active']) ) : ?><span><?php echo $infos['active']; ?></span><?php endif; ?>
              </label>
              <div>
                <?php echo $infos['description']; ?>
              </div>
            </li>
          <?php endforeach; ?>
        </ul>
      </div>
      <?php if ($box == 2): ?>
        </div>
        <?php $box = 1; ?>
      <?php else: ?>
        <?php $box++; ?>
      <?php endif; ?>
    <?php endforeach; ?>

    <?php if ($box == 1): ?>
      </div>
    <?php endif; ?>
  </div>

</div>
