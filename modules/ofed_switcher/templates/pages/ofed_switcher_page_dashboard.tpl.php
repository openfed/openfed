<div class="dashboard span-12">
    <div class="span-4">
      <div class="dashbox tools blue ">
        <h2><?php echo t('Quick Infos') ?></h2>
        <div class="dashbox-content">
          <ul>
            <li class="analytics">
              <a href="http://www.google.com/analytics" target="_blank"><?php print t('Access Google Analytics') ?></a>
            </li>
            <li class="cms">
              <a href="<?php echo base_path(); ?>sites/all/themes/cms_theme/cms-guide.pdf" target="_blank"><?php print t('Download CMS Guide (pdf)') ?></a>
            </li>
          </ul>
        </div>
      </div>
    </div>

    <div class="span-8">
      <?php if ( !empty($dashboard['content']) ): ?>
        <div class="dashbox span-12">
          <h2><?php print t('Create Content') ?></h2>
          <div class="dashbox-content">
            <ul>
              <?php foreach($dashboard['content'] as $label => $links): ?>
                <li>
                  <label><?php echo $label; ?></label>
                  <?php echo l(key($links), $links[key($links)], array('html' => TRUE)); ?>
                </li>
              <?php endforeach; ?>
            </ul>
          </div>
        </div>
      <?php endif; ?>

      <div>
        <?php if( isset($dashboard['user']) ): ?>
          <div class="dashbox orange span-6">
            <h2><?php print t('Manage User') ?></h2>
            <div class="dashbox-content">
              <ul>
                <?php foreach($dashboard['user'] as $label => $links): ?>
                  <li>
                    <label><?php echo $label; ?></label>
                    <?php echo l(key($links), $links[key($links)], array('html' => TRUE)); ?>
                  </li>
                <?php endforeach; ?>
              </ul>
            </div>
          </div>
        <?php endif; ?>

        <?php if( isset($dashboard['block']) ): ?>
          <div class="dashbox orange span-6">
            <h2><?php print t('Manage Blocks') ?></h2>
            <div class="dashbox-content">
              <ul>
                <?php foreach($dashboard['block'] as $label => $links): ?>
                  <li>
                    <label><?php echo $label; ?></label>
                    <?php echo l(key($links), $links[key($links)], array('html' => TRUE)); ?>
                  </li>
                <?php endforeach; ?>
              </ul>
            </div>
          </div>
        <?php endif; ?>
      </div>
    </div>
  </div>
