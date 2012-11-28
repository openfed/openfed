<header>
  <div class="container">
    
    <?php if ($logo): ?>
    <!-- Region Logo -->
      <div class="logo">
        <a href="<?php echo url('<front>'); ?>" title="">
          <img src="<?php print $logo ?>" alt="<?php print $site_name ?>" title="<?php print $site_name ?>" id="logo" />
        </a>
      </div>
    <?php endif; ?>
    
    <?php if( !empty($page['tools']) ): ?>
    <!-- Region Tools -->
      <div class="tools">
        <?php print render($page['tools']); ?>
      </div>	
    <?php endif; ?>
    
    <?php if( !empty($page['header']) ): ?>
    <!-- Region Header -->
      <div class="header">
        <?php print render($page['header']); ?>
      </div>	
    <?php endif; ?>
    
  </div>
</header>

<section class="navigation">
  <div class="container">
    
	<!-- Region Navigation -->	
	<nav class="cms-menu">
      <?php print render($page['navigation']); ?>
      <?php if( theme_get_setting('cms_theme_toggle_quickinfos') && $user->uid) : ?>
        <ul class="quick-info menu clearfix">
          <li class="expanded"><span class="menu-item-container"><?php echo t('Quick Infos') ?></span>
            <ul class="menu">
              <li><?php echo '<a class="lk-quick" href="http://www.google.com/analytics" target="_blank" >Google Analytics</a>'; ?></li>
              <li><?php echo '<a class="lk-quick" href="'.base_path().'sites/all/themes/cms_theme/cms-guide.pdf" target="_blank" >CMS Guide</a>'; ?></li>
            </ul>
          </li>
        </ul>
      <?php endif; ?>
	</nav>
      
  </div>
</section>


<?php if( !empty($page['top']) ): ?>
<!-- Region top -->
  <section class="top">
    <div class="container">
      <div class="top">
        <?php print render($page['top']); ?>
      </div>	
    </div>
  </section>
<?php endif; ?>


<?php if ( theme_get_setting('cms_theme_breadcrumb_display') && $breadcrumb): ?>
<!-- Region Breadcrumb -->
  <nav class="breadcrumb"><?php print $breadcrumb; ?></nav>
<?php endif; ?>

  
<section class="site">
  <div class="container">
    
    <?php if ( !empty($page['sidebar_first']) ): ?>
    <!-- Region Left -->
      <aside class="aside-left <?php echo $class_left; ?>">
        <?php echo render( $page['sidebar_first'] ); ?>
      </aside>
    <?php endif; ?>
    
    <div class="maincontent <?php echo $class_content; ?>">
      <!-- Region Content -->
      <?php if ( theme_get_setting('cms_theme_toggle_message') && $messages): ?>
      <!-- messages -->
        <div id="messages" class="clear clearfix"><?php print $messages; ?></div>
      <?php endif; ?>

      <?php print render($title_prefix); ?>
      <?php if ($title): ?>
        <h1><?php print $title; ?></h1>
      <?php endif; ?>
      <?php print render($title_suffix); ?>

      <?php if ( theme_get_setting('cms_theme_toggle_tabs') && $tabs = render($tabs) ): ?>
        <div class="tabs"><?php print $tabs; ?></div>
      <?php endif; ?>

      <?php if ( theme_get_setting('cms_theme_toggle_actions') && $action_links): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?>

      <?php echo render($page['content_top']); ?>
      <?php echo render($page['content']); ?>
      <?php echo render($page['content_bottom']); ?>
    </div>
    
    <?php if ( !empty($page['sidebar_second']) ): ?>
    <!-- Region Right -->
      <aside class="aside-right <?php echo $class_right; ?>">
        <?php echo render( $page['sidebar_second'] ); ?>
      </aside>
    <?php endif; ?>
    
  </div>
</section>

  
<?php if ( !empty($page['bottom']) ): ?>
<!-- bottom -->
  <section class="bottom">
    <div class="container"><?php echo render($page['bottom']); ?></div>
  </section>
<?php endif; ?>


<footer>
  <div class="container">
    
    <?php if ( !empty($page['footer']) ) : ?>
    <!-- Region Footer -->
      <div class="row">
        <?php echo render($page['footer']); ?>
      </div>
    <?php endif; ?>

    <?php if ( theme_get_setting('cms_theme_copyright_display') || theme_get_setting('cms_theme_toggle_sponsor') ): ?>
      <div class="row">
        
        <?php if ( theme_get_setting('cms_theme_copyright_display') && theme_get_setting('cms_theme_copyright_label') != '' ): ?>
        <!-- Region Copyright -->
          <div class="copyright span-9">
            <p><?php echo theme_get_setting('cms_theme_copyright_label'); ?> - <?php print $site_name ?></p>
          </div>
        <?php endif; ?>
        
        <?php if ( theme_get_setting('cms_theme_toggle_sponsor') ): ?>
        <!-- Region Sponsor -->
          <div class="sponsor span-3">
            <p><a href="http://www.blue4you.be" target="_blank" title="Webdesign by Blue4You">Webdesign</a> by Blue4You</p>
          </div>
        <?php endif; ?>
        
      </div>
    <?php endif; ?>
    
  </div>
</footer>