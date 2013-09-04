


<!DOCTYPE html>
<html>
  <head prefix="og: http://ogp.me/ns# fb: http://ogp.me/ns/fb# githubog: http://ogp.me/ns/fb/githubog#">
    <meta charset='utf-8'>
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <title>imagesloaded/jquery.imagesloaded.js at v2.1.2 · desandro/imagesloaded · GitHub</title>
    <link rel="search" type="application/opensearchdescription+xml" href="/opensearch.xml" title="GitHub" />
    <link rel="fluid-icon" href="https://github.com/fluidicon.png" title="GitHub" />
    <link rel="apple-touch-icon" sizes="57x57" href="/apple-touch-icon-114.png" />
    <link rel="apple-touch-icon" sizes="114x114" href="/apple-touch-icon-114.png" />
    <link rel="apple-touch-icon" sizes="72x72" href="/apple-touch-icon-144.png" />
    <link rel="apple-touch-icon" sizes="144x144" href="/apple-touch-icon-144.png" />
    <link rel="logo" type="image/svg" href="https://github-media-downloads.s3.amazonaws.com/github-logo.svg" />
    <meta property="og:image" content="https://github.global.ssl.fastly.net/images/modules/logos_page/Octocat.png">
    <meta name="hostname" content="github-fe125-cp1-prd.iad.github.net">
    <meta name="ruby" content="ruby 1.9.3p194-tcs-github-tcmalloc (2012-05-25, TCS patched 2012-05-27, GitHub v1.0.32) [x86_64-linux]">
    <link rel="assets" href="https://github.global.ssl.fastly.net/">
    <link rel="xhr-socket" href="/_sockets" />
    
    


    <meta name="msapplication-TileImage" content="/windows-tile.png" />
    <meta name="msapplication-TileColor" content="#ffffff" />
    <meta name="selected-link" value="repo_source" data-pjax-transient />
    <meta content="collector.githubapp.com" name="octolytics-host" /><meta content="github" name="octolytics-app-id" />
    

    
    
    <link rel="icon" type="image/x-icon" href="/favicon.ico" />

    <meta content="authenticity_token" name="csrf-param" />
<meta content="2XzX0TZtL1zFkrwTka/7G55v3Kupe3spfqjDP6RT2W8=" name="csrf-token" />

    <link href="https://github.global.ssl.fastly.net/assets/github-d5cd1fc5dca65c99b46e668177e3ecc40eb1bfa5.css" media="all" rel="stylesheet" type="text/css" />
    <link href="https://github.global.ssl.fastly.net/assets/github2-672985c1cda50a743fddd61eda75c37c004fb1c8.css" media="all" rel="stylesheet" type="text/css" />
    


      <script src="https://github.global.ssl.fastly.net/assets/frameworks-f86a2975a82dceee28e5afe598d1ebbfd7109d79.js" type="text/javascript"></script>
      <script src="https://github.global.ssl.fastly.net/assets/github-d10bb7847b7c3c53c628a36747fc0b6e0be06342.js" type="text/javascript"></script>
      
      <meta http-equiv="x-pjax-version" content="f6ca1a16fd5d9c73cf8a1d17181d87cb">

        <link data-pjax-transient rel='permalink' href='/desandro/imagesloaded/blob/d90af1bc980f15f8525a1affe7db18265ad8c5e0/jquery.imagesloaded.js'>
  <meta property="og:title" content="imagesloaded"/>
  <meta property="og:type" content="githubog:gitrepository"/>
  <meta property="og:url" content="https://github.com/desandro/imagesloaded"/>
  <meta property="og:image" content="https://github.global.ssl.fastly.net/images/gravatars/gravatar-user-420.png"/>
  <meta property="og:site_name" content="GitHub"/>
  <meta property="og:description" content="imagesloaded - JavaScript is all like &quot;You images done yet or what?&quot;"/>

  <meta name="description" content="imagesloaded - JavaScript is all like &quot;You images done yet or what?&quot;" />

  <meta content="85566" name="octolytics-dimension-user_id" /><meta content="desandro" name="octolytics-dimension-user_login" /><meta content="2269353" name="octolytics-dimension-repository_id" /><meta content="desandro/imagesloaded" name="octolytics-dimension-repository_nwo" /><meta content="true" name="octolytics-dimension-repository_public" /><meta content="false" name="octolytics-dimension-repository_is_fork" /><meta content="2269353" name="octolytics-dimension-repository_network_root_id" /><meta content="desandro/imagesloaded" name="octolytics-dimension-repository_network_root_nwo" />
  <link href="https://github.com/desandro/imagesloaded/commits/v2.1.2.atom" rel="alternate" title="Recent Commits to imagesloaded:v2.1.2" type="application/atom+xml" />

  </head>


  <body class="logged_out page-blob  vis-public env-production ">

    <div class="wrapper">
      
      
      


      
      <div class="header header-logged-out">
  <div class="container clearfix">

    <a class="header-logo-wordmark" href="https://github.com/">
      <span class="mega-octicon octicon-logo-github"></span>
    </a>

    <div class="header-actions">
        <a class="button primary" href="/signup">Sign up</a>
      <a class="button" href="/login?return_to=%2Fdesandro%2Fimagesloaded%2Fblob%2Fv2.1.2%2Fjquery.imagesloaded.js">Sign in</a>
    </div>

    <div class="command-bar js-command-bar  in-repository">


      <ul class="top-nav">
          <li class="explore"><a href="/explore">Explore</a></li>
        <li class="features"><a href="/features">Features</a></li>
          <li class="enterprise"><a href="https://enterprise.github.com/">Enterprise</a></li>
          <li class="blog"><a href="/blog">Blog</a></li>
      </ul>
        <form accept-charset="UTF-8" action="/search" class="command-bar-form" id="top_search_form" method="get">

<input type="text" data-hotkey="/ s" name="q" id="js-command-bar-field" placeholder="Search or type a command" tabindex="1" autocapitalize="off"
    
    
      data-repo="desandro/imagesloaded"
      data-branch="v2.1.2"
      data-sha="9d52021f36e00cc09bbb8964e45f2dac7572223e"
  >

    <input type="hidden" name="nwo" value="desandro/imagesloaded" />

    <div class="select-menu js-menu-container js-select-menu search-context-select-menu">
      <span class="minibutton select-menu-button js-menu-target">
        <span class="js-select-button">This repository</span>
      </span>

      <div class="select-menu-modal-holder js-menu-content js-navigation-container">
        <div class="select-menu-modal">

          <div class="select-menu-item js-navigation-item js-this-repository-navigation-item selected">
            <span class="select-menu-item-icon octicon octicon-check"></span>
            <input type="radio" class="js-search-this-repository" name="search_target" value="repository" checked="checked" />
            <div class="select-menu-item-text js-select-button-text">This repository</div>
          </div> <!-- /.select-menu-item -->

          <div class="select-menu-item js-navigation-item js-all-repositories-navigation-item">
            <span class="select-menu-item-icon octicon octicon-check"></span>
            <input type="radio" name="search_target" value="global" />
            <div class="select-menu-item-text js-select-button-text">All repositories</div>
          </div> <!-- /.select-menu-item -->

        </div>
      </div>
    </div>

  <span class="octicon help tooltipped downwards" title="Show command bar help">
    <span class="octicon octicon-question"></span>
  </span>


  <input type="hidden" name="ref" value="cmdform">

</form>
    </div>

  </div>
</div>


      


          <div class="site" itemscope itemtype="http://schema.org/WebPage">
    
    <div class="pagehead repohead instapaper_ignore readability-menu">
      <div class="container">
        

<ul class="pagehead-actions">


  <li>
  <a href="/login?return_to=%2Fdesandro%2Fimagesloaded"
  class="minibutton with-count js-toggler-target star-button entice tooltipped upwards"
  title="You must be signed in to use this feature" rel="nofollow">
  <span class="octicon octicon-star"></span>Star
</a>
<a class="social-count js-social-count" href="/desandro/imagesloaded/stargazers">
  1,863
</a>

  </li>

    <li>
      <a href="/login?return_to=%2Fdesandro%2Fimagesloaded"
        class="minibutton with-count js-toggler-target fork-button entice tooltipped upwards"
        title="You must be signed in to fork a repository" rel="nofollow">
        <span class="octicon octicon-git-branch"></span>Fork
      </a>
      <a href="/desandro/imagesloaded/network" class="social-count">
        408
      </a>
    </li>
</ul>

        <h1 itemscope itemtype="http://data-vocabulary.org/Breadcrumb" class="entry-title public">
          <span class="repo-label"><span>public</span></span>
          <span class="mega-octicon octicon-repo"></span>
          <span class="author">
            <a href="/desandro" class="url fn" itemprop="url" rel="author"><span itemprop="title">desandro</span></a></span
          ><span class="repohead-name-divider">/</span><strong
          ><a href="/desandro/imagesloaded" class="js-current-repository js-repo-home-link">imagesloaded</a></strong>

          <span class="page-context-loader">
            <img alt="Octocat-spinner-32" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
          </span>

        </h1>
      </div><!-- /.container -->
    </div><!-- /.repohead -->

    <div class="container">

      <div class="repository-with-sidebar repo-container ">

        <div class="repository-sidebar">
            

<div class="repo-nav repo-nav-full js-repository-container-pjax js-octicon-loaders">
  <div class="repo-nav-contents">
    <ul class="repo-menu">
      <li class="tooltipped leftwards" title="Code">
        <a href="/desandro/imagesloaded/tree/v2.1.2" aria-label="Code" class="js-selected-navigation-item selected" data-gotokey="c" data-pjax="true" data-selected-links="repo_source repo_downloads repo_commits repo_tags repo_branches /desandro/imagesloaded/tree/v2.1.2">
          <span class="octicon octicon-code"></span> <span class="full-word">Code</span>
          <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>

        <li class="tooltipped leftwards" title="Issues">
          <a href="/desandro/imagesloaded/issues" aria-label="Issues" class="js-selected-navigation-item js-disable-pjax" data-gotokey="i" data-selected-links="repo_issues /desandro/imagesloaded/issues">
            <span class="octicon octicon-issue-opened"></span> <span class="full-word">Issues</span>
            <span class='counter'>16</span>
            <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>        </li>

      <li class="tooltipped leftwards" title="Pull Requests"><a href="/desandro/imagesloaded/pulls" aria-label="Pull Requests" class="js-selected-navigation-item js-disable-pjax" data-gotokey="p" data-selected-links="repo_pulls /desandro/imagesloaded/pulls">
            <span class="octicon octicon-git-pull-request"></span> <span class="full-word">Pull Requests</span>
            <span class='counter'>3</span>
            <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>


        <li class="tooltipped leftwards" title="Wiki">
          <a href="/desandro/imagesloaded/wiki" aria-label="Wiki" class="js-selected-navigation-item " data-pjax="true" data-selected-links="repo_wiki /desandro/imagesloaded/wiki">
            <span class="octicon octicon-book"></span> <span class="full-word">Wiki</span>
            <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>        </li>
    </ul>
    <div class="repo-menu-separator"></div>
    <ul class="repo-menu">

      <li class="tooltipped leftwards" title="Pulse">
        <a href="/desandro/imagesloaded/pulse" aria-label="Pulse" class="js-selected-navigation-item " data-pjax="true" data-selected-links="pulse /desandro/imagesloaded/pulse">
          <span class="octicon octicon-pulse"></span> <span class="full-word">Pulse</span>
          <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>

      <li class="tooltipped leftwards" title="Graphs">
        <a href="/desandro/imagesloaded/graphs" aria-label="Graphs" class="js-selected-navigation-item " data-pjax="true" data-selected-links="repo_graphs repo_contributors /desandro/imagesloaded/graphs">
          <span class="octicon octicon-graph"></span> <span class="full-word">Graphs</span>
          <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>

      <li class="tooltipped leftwards" title="Network">
        <a href="/desandro/imagesloaded/network" aria-label="Network" class="js-selected-navigation-item js-disable-pjax" data-selected-links="repo_network /desandro/imagesloaded/network">
          <span class="octicon octicon-git-branch"></span> <span class="full-word">Network</span>
          <img alt="Octocat-spinner-32" class="mini-loader" height="16" src="https://github.global.ssl.fastly.net/images/spinners/octocat-spinner-32.gif" width="16" />
</a>      </li>
    </ul>


  </div>
</div>

            <div class="only-with-full-nav">
              

  

<div class="clone-url open"
  data-protocol-type="http"
  data-url="/users/set_protocol?protocol_selector=http&amp;protocol_type=clone">
  <h3><strong>HTTPS</strong> clone URL</h3>

  <input type="text" class="clone js-url-field"
         value="https://github.com/desandro/imagesloaded.git" readonly="readonly">

  <span class="js-zeroclipboard url-box-clippy minibutton zeroclipboard-button" data-clipboard-text="https://github.com/desandro/imagesloaded.git" data-copied-hint="copied!" title="copy to clipboard"><span class="octicon octicon-clippy"></span></span>
</div>

  

<div class="clone-url "
  data-protocol-type="subversion"
  data-url="/users/set_protocol?protocol_selector=subversion&amp;protocol_type=clone">
  <h3><strong>Subversion</strong> checkout URL</h3>

  <input type="text" class="clone js-url-field"
         value="https://github.com/desandro/imagesloaded" readonly="readonly">

  <span class="js-zeroclipboard url-box-clippy minibutton zeroclipboard-button" data-clipboard-text="https://github.com/desandro/imagesloaded" data-copied-hint="copied!" title="copy to clipboard"><span class="octicon octicon-clippy"></span></span>
</div>



<p class="clone-options">You can clone with
    <a href="#" class="js-clone-selector" data-protocol="http">HTTPS</a>,
    <a href="#" class="js-clone-selector" data-protocol="subversion">Subversion</a>,
  and <a href="https://help.github.com/articles/which-remote-url-should-i-use">other methods.</a>
</p>



                <a href="/desandro/imagesloaded/archive/v2.1.2.zip"
                   class="minibutton sidebar-button"
                   title="Download this repository as a zip file"
                   rel="nofollow">
                  <span class="octicon octicon-cloud-download"></span>
                  Download ZIP
                </a>
            </div>
        </div><!-- /.repository-sidebar -->

        <div id="js-repo-pjax-container" class="repository-content context-loader-container" data-pjax-container>
          


<!-- blob contrib key: blob_contributors:v21:4d7cfc1f1d7609adceb98fe3a9287f58 -->
<!-- blob contrib frag key: views10/v8/blob_contributors:v21:4d7cfc1f1d7609adceb98fe3a9287f58 -->

<p title="This is a placeholder element" class="js-history-link-replace hidden"></p>

<a href="/desandro/imagesloaded/find/v2.1.2" data-pjax data-hotkey="t" style="display:none">Show File Finder</a>

<div class="file-navigation">
  


<div class="select-menu js-menu-container js-select-menu" >
  <span class="minibutton select-menu-button js-menu-target" data-hotkey="w"
    data-master-branch="master"
    data-ref="v2.1.2" role="button" aria-label="Switch branches or tags">
    <span class="octicon octicon-tag"></span>
    <i>tag:</i>
    <span class="js-select-button">v2.1.2</span>
  </span>

  <div class="select-menu-modal-holder js-menu-content js-navigation-container" data-pjax>

    <div class="select-menu-modal">
      <div class="select-menu-header">
        <span class="select-menu-title">Switch branches/tags</span>
        <span class="octicon octicon-remove-close js-menu-close"></span>
      </div> <!-- /.select-menu-header -->

      <div class="select-menu-filters">
        <div class="select-menu-text-filter">
          <input type="text" aria-label="Filter branches/tags" id="context-commitish-filter-field" class="js-filterable-field js-navigation-enable" placeholder="Filter branches/tags">
        </div>
        <div class="select-menu-tabs">
          <ul>
            <li class="select-menu-tab">
              <a href="#" data-tab-filter="branches" class="js-select-menu-tab">Branches</a>
            </li>
            <li class="select-menu-tab">
              <a href="#" data-tab-filter="tags" class="js-select-menu-tab">Tags</a>
            </li>
          </ul>
        </div><!-- /.select-menu-tabs -->
      </div><!-- /.select-menu-filters -->

      <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket" data-tab-filter="branches">

        <div data-filterable-for="context-commitish-filter-field" data-filterable-type="substring">


            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/desandro/imagesloaded/blob/gh-pages/jquery.imagesloaded.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="gh-pages" data-skip-pjax="true" rel="nofollow" title="gh-pages">gh-pages</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/desandro/imagesloaded/blob/master/jquery.imagesloaded.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="master" data-skip-pjax="true" rel="nofollow" title="master">master</a>
            </div> <!-- /.select-menu-item -->
        </div>

          <div class="select-menu-no-results">Nothing to show</div>
      </div> <!-- /.select-menu-list -->

      <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket" data-tab-filter="tags">
        <div data-filterable-for="context-commitish-filter-field" data-filterable-type="substring">


            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/desandro/imagesloaded/tree/v3.0.4/jquery.imagesloaded.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="v3.0.4" data-skip-pjax="true" rel="nofollow" title="v3.0.4">v3.0.4</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/desandro/imagesloaded/tree/v3.0.3/jquery.imagesloaded.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="v3.0.3" data-skip-pjax="true" rel="nofollow" title="v3.0.3">v3.0.3</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/desandro/imagesloaded/tree/v3.0.2/jquery.imagesloaded.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="v3.0.2" data-skip-pjax="true" rel="nofollow" title="v3.0.2">v3.0.2</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/desandro/imagesloaded/tree/v3.0.1/jquery.imagesloaded.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="v3.0.1" data-skip-pjax="true" rel="nofollow" title="v3.0.1">v3.0.1</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/desandro/imagesloaded/tree/v3.0.0/jquery.imagesloaded.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="v3.0.0" data-skip-pjax="true" rel="nofollow" title="v3.0.0">v3.0.0</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item selected">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/desandro/imagesloaded/tree/v2.1.2/jquery.imagesloaded.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="v2.1.2" data-skip-pjax="true" rel="nofollow" title="v2.1.2">v2.1.2</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/desandro/imagesloaded/tree/v2.1.1/jquery.imagesloaded.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="v2.1.1" data-skip-pjax="true" rel="nofollow" title="v2.1.1">v2.1.1</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/desandro/imagesloaded/tree/v2.1.0/jquery.imagesloaded.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="v2.1.0" data-skip-pjax="true" rel="nofollow" title="v2.1.0">v2.1.0</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/desandro/imagesloaded/tree/v2.0.1/jquery.imagesloaded.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="v2.0.1" data-skip-pjax="true" rel="nofollow" title="v2.0.1">v2.0.1</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/desandro/imagesloaded/tree/v2.0.0/jquery.imagesloaded.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="v2.0.0" data-skip-pjax="true" rel="nofollow" title="v2.0.0">v2.0.0</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/desandro/imagesloaded/tree/v1.2.4/jquery.imagesloaded.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="v1.2.4" data-skip-pjax="true" rel="nofollow" title="v1.2.4">v1.2.4</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/desandro/imagesloaded/tree/v1.2.3/jquery.imagesloaded.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="v1.2.3" data-skip-pjax="true" rel="nofollow" title="v1.2.3">v1.2.3</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/desandro/imagesloaded/tree/v1.2.2/jquery.imagesloaded.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="v1.2.2" data-skip-pjax="true" rel="nofollow" title="v1.2.2">v1.2.2</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/desandro/imagesloaded/tree/v1.2.1/jquery.imagesloaded.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="v1.2.1" data-skip-pjax="true" rel="nofollow" title="v1.2.1">v1.2.1</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/desandro/imagesloaded/tree/v1.2.0/jquery.imagesloaded.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="v1.2.0" data-skip-pjax="true" rel="nofollow" title="v1.2.0">v1.2.0</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/desandro/imagesloaded/tree/v1.1.0/jquery.imagesloaded.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="v1.1.0" data-skip-pjax="true" rel="nofollow" title="v1.1.0">v1.1.0</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/desandro/imagesloaded/tree/v1.0.4/jquery.imagesloaded.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="v1.0.4" data-skip-pjax="true" rel="nofollow" title="v1.0.4">v1.0.4</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/desandro/imagesloaded/tree/v1.0.3/jquery.imagesloaded.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="v1.0.3" data-skip-pjax="true" rel="nofollow" title="v1.0.3">v1.0.3</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/desandro/imagesloaded/tree/v1.0.2/jquery.imagesloaded.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="v1.0.2" data-skip-pjax="true" rel="nofollow" title="v1.0.2">v1.0.2</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/desandro/imagesloaded/tree/v1.0.1/jquery.imagesloaded.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="v1.0.1" data-skip-pjax="true" rel="nofollow" title="v1.0.1">v1.0.1</a>
            </div> <!-- /.select-menu-item -->
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/desandro/imagesloaded/tree/v1.0.0/jquery.imagesloaded.js" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="v1.0.0" data-skip-pjax="true" rel="nofollow" title="v1.0.0">v1.0.0</a>
            </div> <!-- /.select-menu-item -->
        </div>

        <div class="select-menu-no-results">Nothing to show</div>
      </div> <!-- /.select-menu-list -->

    </div> <!-- /.select-menu-modal -->
  </div> <!-- /.select-menu-modal-holder -->
</div> <!-- /.select-menu -->

  <div class="breadcrumb">
    <span class='repo-root js-repo-root'><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/desandro/imagesloaded/tree/v2.1.2" data-branch="v2.1.2" data-direction="back" data-pjax="true" itemscope="url"><span itemprop="title">imagesloaded</span></a></span></span><span class="separator"> / </span><strong class="final-path">jquery.imagesloaded.js</strong> <span class="js-zeroclipboard minibutton zeroclipboard-button" data-clipboard-text="jquery.imagesloaded.js" data-copied-hint="copied!" title="copy to clipboard"><span class="octicon octicon-clippy"></span></span>
  </div>
</div>


  
  <div class="commit file-history-tease">
    <img class="main-avatar" height="24" src="https://1.gravatar.com/avatar/08452845db61b0edbb0c3c16d9599770?d=https%3A%2F%2Fidenticons.github.com%2F906a7cf4657ab3f2f031889a0ed25057.png&amp;s=140" width="24" />
    <span class="author"><a href="/desandro" rel="author">desandro</a></span>
    <time class="js-relative-date" datetime="2013-05-20T14:33:24-07:00" title="2013-05-20 14:33:24">May 20, 2013</time>
    <div class="commit-title">
        <a href="/desandro/imagesloaded/commit/d90af1bc980f15f8525a1affe7db18265ad8c5e0" class="message" data-pjax="true" title="component.json -&gt; bower.json; Ref #65">component.json -&gt; bower.json; Ref</a> <a href="https://github.com/desandro/imagesloaded/issues/65" class="issue-link" title="v3 rewrite">#65</a>
    </div>

    <div class="participation">
      <p class="quickstat"><a href="#blob_contributors_box" rel="facebox"><strong>5</strong> contributors</a></p>
          <a class="avatar tooltipped downwards" title="desandro" href="/desandro/imagesloaded/commits/v2.1.2/jquery.imagesloaded.js?author=desandro"><img height="20" src="https://1.gravatar.com/avatar/08452845db61b0edbb0c3c16d9599770?d=https%3A%2F%2Fidenticons.github.com%2F906a7cf4657ab3f2f031889a0ed25057.png&amp;s=140" width="20" /></a>
    <a class="avatar tooltipped downwards" title="Darsain" href="/desandro/imagesloaded/commits/v2.1.2/jquery.imagesloaded.js?author=Darsain"><img height="20" src="https://1.gravatar.com/avatar/d4f27d97239ac248cfcd9d4a50617644?d=https%3A%2F%2Fidenticons.github.com%2F18ac726b5e11225a9c8132f2657d062d.png&amp;s=140" width="20" /></a>
    <a class="avatar tooltipped downwards" title="mathiasbynens" href="/desandro/imagesloaded/commits/v2.1.2/jquery.imagesloaded.js?author=mathiasbynens"><img height="20" src="https://0.gravatar.com/avatar/24e08a9ea84deb17ae121074d0f17125?d=https%3A%2F%2Fidenticons.github.com%2F40b157a07054152a85010ad58a585833.png&amp;s=140" width="20" /></a>
    <a class="avatar tooltipped downwards" title="sdepold" href="/desandro/imagesloaded/commits/v2.1.2/jquery.imagesloaded.js?author=sdepold"><img height="20" src="https://1.gravatar.com/avatar/f30479a06db175157387334e03766420?d=https%3A%2F%2Fidenticons.github.com%2F425df7cd4ffe4006cabfbe0a9a9bca7b.png&amp;s=140" width="20" /></a>
    <a class="avatar tooltipped downwards" title="treyhunner" href="/desandro/imagesloaded/commits/v2.1.2/jquery.imagesloaded.js?author=treyhunner"><img height="20" src="https://1.gravatar.com/avatar/945d10168a7817c64276c164a57fa8de?d=https%3A%2F%2Fidenticons.github.com%2Fada8bf4ef444e0e1f8523bf03b601846.png&amp;s=140" width="20" /></a>


    </div>
    <div id="blob_contributors_box" style="display:none">
      <h2 class="facebox-header">Users who have contributed to this file</h2>
      <ul class="facebox-user-list">
        <li class="facebox-user-list-item">
          <img height="24" src="https://1.gravatar.com/avatar/08452845db61b0edbb0c3c16d9599770?d=https%3A%2F%2Fidenticons.github.com%2F906a7cf4657ab3f2f031889a0ed25057.png&amp;s=140" width="24" />
          <a href="/desandro">desandro</a>
        </li>
        <li class="facebox-user-list-item">
          <img height="24" src="https://1.gravatar.com/avatar/d4f27d97239ac248cfcd9d4a50617644?d=https%3A%2F%2Fidenticons.github.com%2F18ac726b5e11225a9c8132f2657d062d.png&amp;s=140" width="24" />
          <a href="/Darsain">Darsain</a>
        </li>
        <li class="facebox-user-list-item">
          <img height="24" src="https://0.gravatar.com/avatar/24e08a9ea84deb17ae121074d0f17125?d=https%3A%2F%2Fidenticons.github.com%2F40b157a07054152a85010ad58a585833.png&amp;s=140" width="24" />
          <a href="/mathiasbynens">mathiasbynens</a>
        </li>
        <li class="facebox-user-list-item">
          <img height="24" src="https://1.gravatar.com/avatar/f30479a06db175157387334e03766420?d=https%3A%2F%2Fidenticons.github.com%2F425df7cd4ffe4006cabfbe0a9a9bca7b.png&amp;s=140" width="24" />
          <a href="/sdepold">sdepold</a>
        </li>
        <li class="facebox-user-list-item">
          <img height="24" src="https://1.gravatar.com/avatar/945d10168a7817c64276c164a57fa8de?d=https%3A%2F%2Fidenticons.github.com%2Fada8bf4ef444e0e1f8523bf03b601846.png&amp;s=140" width="24" />
          <a href="/treyhunner">treyhunner</a>
        </li>
      </ul>
    </div>
  </div>


<div id="files" class="bubble">
  <div class="file">
    <div class="meta">
      <div class="info">
        <span class="icon"><b class="octicon octicon-file-text"></b></span>
        <span class="mode" title="File Mode">file</span>
          <span>125 lines (104 sloc)</span>
        <span>3.388 kb</span>
      </div>
      <div class="actions">
        <div class="button-group">
              <a class="minibutton disabled js-entice" href=""
                 data-entice="You must be signed in to make or propose changes">Edit</a>
          <a href="/desandro/imagesloaded/raw/v2.1.2/jquery.imagesloaded.js" class="button minibutton " id="raw-url">Raw</a>
            <a href="/desandro/imagesloaded/blame/v2.1.2/jquery.imagesloaded.js" class="button minibutton ">Blame</a>
          <a href="/desandro/imagesloaded/commits/v2.1.2/jquery.imagesloaded.js" class="button minibutton " rel="nofollow">History</a>
        </div><!-- /.button-group -->
            <a class="minibutton danger empty-icon js-entice" href=""
               data-entice="You must be signed in and on a branch to make or propose changes">
            Delete
          </a>
      </div><!-- /.actions -->

    </div>
        <div class="blob-wrapper data type-javascript js-blob-data">
        <table class="file-code file-diff">
          <tr class="file-code-line">
            <td class="blob-line-nums">
              <span id="L1" rel="#L1">1</span>
<span id="L2" rel="#L2">2</span>
<span id="L3" rel="#L3">3</span>
<span id="L4" rel="#L4">4</span>
<span id="L5" rel="#L5">5</span>
<span id="L6" rel="#L6">6</span>
<span id="L7" rel="#L7">7</span>
<span id="L8" rel="#L8">8</span>
<span id="L9" rel="#L9">9</span>
<span id="L10" rel="#L10">10</span>
<span id="L11" rel="#L11">11</span>
<span id="L12" rel="#L12">12</span>
<span id="L13" rel="#L13">13</span>
<span id="L14" rel="#L14">14</span>
<span id="L15" rel="#L15">15</span>
<span id="L16" rel="#L16">16</span>
<span id="L17" rel="#L17">17</span>
<span id="L18" rel="#L18">18</span>
<span id="L19" rel="#L19">19</span>
<span id="L20" rel="#L20">20</span>
<span id="L21" rel="#L21">21</span>
<span id="L22" rel="#L22">22</span>
<span id="L23" rel="#L23">23</span>
<span id="L24" rel="#L24">24</span>
<span id="L25" rel="#L25">25</span>
<span id="L26" rel="#L26">26</span>
<span id="L27" rel="#L27">27</span>
<span id="L28" rel="#L28">28</span>
<span id="L29" rel="#L29">29</span>
<span id="L30" rel="#L30">30</span>
<span id="L31" rel="#L31">31</span>
<span id="L32" rel="#L32">32</span>
<span id="L33" rel="#L33">33</span>
<span id="L34" rel="#L34">34</span>
<span id="L35" rel="#L35">35</span>
<span id="L36" rel="#L36">36</span>
<span id="L37" rel="#L37">37</span>
<span id="L38" rel="#L38">38</span>
<span id="L39" rel="#L39">39</span>
<span id="L40" rel="#L40">40</span>
<span id="L41" rel="#L41">41</span>
<span id="L42" rel="#L42">42</span>
<span id="L43" rel="#L43">43</span>
<span id="L44" rel="#L44">44</span>
<span id="L45" rel="#L45">45</span>
<span id="L46" rel="#L46">46</span>
<span id="L47" rel="#L47">47</span>
<span id="L48" rel="#L48">48</span>
<span id="L49" rel="#L49">49</span>
<span id="L50" rel="#L50">50</span>
<span id="L51" rel="#L51">51</span>
<span id="L52" rel="#L52">52</span>
<span id="L53" rel="#L53">53</span>
<span id="L54" rel="#L54">54</span>
<span id="L55" rel="#L55">55</span>
<span id="L56" rel="#L56">56</span>
<span id="L57" rel="#L57">57</span>
<span id="L58" rel="#L58">58</span>
<span id="L59" rel="#L59">59</span>
<span id="L60" rel="#L60">60</span>
<span id="L61" rel="#L61">61</span>
<span id="L62" rel="#L62">62</span>
<span id="L63" rel="#L63">63</span>
<span id="L64" rel="#L64">64</span>
<span id="L65" rel="#L65">65</span>
<span id="L66" rel="#L66">66</span>
<span id="L67" rel="#L67">67</span>
<span id="L68" rel="#L68">68</span>
<span id="L69" rel="#L69">69</span>
<span id="L70" rel="#L70">70</span>
<span id="L71" rel="#L71">71</span>
<span id="L72" rel="#L72">72</span>
<span id="L73" rel="#L73">73</span>
<span id="L74" rel="#L74">74</span>
<span id="L75" rel="#L75">75</span>
<span id="L76" rel="#L76">76</span>
<span id="L77" rel="#L77">77</span>
<span id="L78" rel="#L78">78</span>
<span id="L79" rel="#L79">79</span>
<span id="L80" rel="#L80">80</span>
<span id="L81" rel="#L81">81</span>
<span id="L82" rel="#L82">82</span>
<span id="L83" rel="#L83">83</span>
<span id="L84" rel="#L84">84</span>
<span id="L85" rel="#L85">85</span>
<span id="L86" rel="#L86">86</span>
<span id="L87" rel="#L87">87</span>
<span id="L88" rel="#L88">88</span>
<span id="L89" rel="#L89">89</span>
<span id="L90" rel="#L90">90</span>
<span id="L91" rel="#L91">91</span>
<span id="L92" rel="#L92">92</span>
<span id="L93" rel="#L93">93</span>
<span id="L94" rel="#L94">94</span>
<span id="L95" rel="#L95">95</span>
<span id="L96" rel="#L96">96</span>
<span id="L97" rel="#L97">97</span>
<span id="L98" rel="#L98">98</span>
<span id="L99" rel="#L99">99</span>
<span id="L100" rel="#L100">100</span>
<span id="L101" rel="#L101">101</span>
<span id="L102" rel="#L102">102</span>
<span id="L103" rel="#L103">103</span>
<span id="L104" rel="#L104">104</span>
<span id="L105" rel="#L105">105</span>
<span id="L106" rel="#L106">106</span>
<span id="L107" rel="#L107">107</span>
<span id="L108" rel="#L108">108</span>
<span id="L109" rel="#L109">109</span>
<span id="L110" rel="#L110">110</span>
<span id="L111" rel="#L111">111</span>
<span id="L112" rel="#L112">112</span>
<span id="L113" rel="#L113">113</span>
<span id="L114" rel="#L114">114</span>
<span id="L115" rel="#L115">115</span>
<span id="L116" rel="#L116">116</span>
<span id="L117" rel="#L117">117</span>
<span id="L118" rel="#L118">118</span>
<span id="L119" rel="#L119">119</span>
<span id="L120" rel="#L120">120</span>
<span id="L121" rel="#L121">121</span>
<span id="L122" rel="#L122">122</span>
<span id="L123" rel="#L123">123</span>
<span id="L124" rel="#L124">124</span>
<span id="L125" rel="#L125">125</span>

            </td>
            <td class="blob-line-code">
                    <div class="highlight"><pre><div class='line' id='LC1'><span class="cm">/*!</span></div><div class='line' id='LC2'><span class="cm"> * jQuery imagesLoaded plugin v2.1.2</span></div><div class='line' id='LC3'><span class="cm"> * http://github.com/desandro/imagesloaded</span></div><div class='line' id='LC4'><span class="cm"> *</span></div><div class='line' id='LC5'><span class="cm"> * MIT License. by Paul Irish et al.</span></div><div class='line' id='LC6'><span class="cm"> */</span></div><div class='line' id='LC7'><br/></div><div class='line' id='LC8'><span class="cm">/*jshint curly: true, eqeqeq: true, noempty: true, strict: true, undef: true, browser: true */</span></div><div class='line' id='LC9'><span class="cm">/*global jQuery: false */</span></div><div class='line' id='LC10'><br/></div><div class='line' id='LC11'><span class="p">;(</span><span class="kd">function</span><span class="p">(</span><span class="nx">$</span><span class="p">,</span> <span class="kc">undefined</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC12'><span class="s1">&#39;use strict&#39;</span><span class="p">;</span></div><div class='line' id='LC13'><br/></div><div class='line' id='LC14'><span class="c1">// blank image data-uri bypasses webkit log warning (thx doug jones)</span></div><div class='line' id='LC15'><span class="kd">var</span> <span class="nx">BLANK</span> <span class="o">=</span> <span class="s1">&#39;data:image/gif;base64,R0lGODlhAQABAIAAAAAAAP///ywAAAAAAQABAAACAUwAOw==&#39;</span><span class="p">;</span></div><div class='line' id='LC16'><br/></div><div class='line' id='LC17'><span class="nx">$</span><span class="p">.</span><span class="nx">fn</span><span class="p">.</span><span class="nx">imagesLoaded</span> <span class="o">=</span> <span class="kd">function</span><span class="p">(</span> <span class="nx">callback</span> <span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC18'>	<span class="kd">var</span> <span class="nx">$this</span> <span class="o">=</span> <span class="k">this</span><span class="p">,</span></div><div class='line' id='LC19'>		<span class="nx">deferred</span> <span class="o">=</span> <span class="nx">$</span><span class="p">.</span><span class="nx">isFunction</span><span class="p">(</span><span class="nx">$</span><span class="p">.</span><span class="nx">Deferred</span><span class="p">)</span> <span class="o">?</span> <span class="nx">$</span><span class="p">.</span><span class="nx">Deferred</span><span class="p">()</span> <span class="o">:</span> <span class="mi">0</span><span class="p">,</span></div><div class='line' id='LC20'>		<span class="nx">hasNotify</span> <span class="o">=</span> <span class="nx">$</span><span class="p">.</span><span class="nx">isFunction</span><span class="p">(</span><span class="nx">deferred</span><span class="p">.</span><span class="nx">notify</span><span class="p">),</span></div><div class='line' id='LC21'>		<span class="nx">$images</span> <span class="o">=</span> <span class="nx">$this</span><span class="p">.</span><span class="nx">find</span><span class="p">(</span><span class="s1">&#39;img&#39;</span><span class="p">).</span><span class="nx">add</span><span class="p">(</span> <span class="nx">$this</span><span class="p">.</span><span class="nx">filter</span><span class="p">(</span><span class="s1">&#39;img&#39;</span><span class="p">)</span> <span class="p">),</span></div><div class='line' id='LC22'>		<span class="nx">loaded</span> <span class="o">=</span> <span class="p">[],</span></div><div class='line' id='LC23'>		<span class="nx">proper</span> <span class="o">=</span> <span class="p">[],</span></div><div class='line' id='LC24'>		<span class="nx">broken</span> <span class="o">=</span> <span class="p">[];</span></div><div class='line' id='LC25'><br/></div><div class='line' id='LC26'>	<span class="c1">// Register deferred callbacks</span></div><div class='line' id='LC27'>	<span class="k">if</span> <span class="p">(</span><span class="nx">$</span><span class="p">.</span><span class="nx">isPlainObject</span><span class="p">(</span><span class="nx">callback</span><span class="p">))</span> <span class="p">{</span></div><div class='line' id='LC28'>		<span class="nx">$</span><span class="p">.</span><span class="nx">each</span><span class="p">(</span><span class="nx">callback</span><span class="p">,</span> <span class="kd">function</span> <span class="p">(</span><span class="nx">key</span><span class="p">,</span> <span class="nx">value</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC29'>			<span class="k">if</span> <span class="p">(</span><span class="nx">key</span> <span class="o">===</span> <span class="s1">&#39;callback&#39;</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC30'>				<span class="nx">callback</span> <span class="o">=</span> <span class="nx">value</span><span class="p">;</span></div><div class='line' id='LC31'>			<span class="p">}</span> <span class="k">else</span> <span class="k">if</span> <span class="p">(</span><span class="nx">deferred</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC32'>				<span class="nx">deferred</span><span class="p">[</span><span class="nx">key</span><span class="p">](</span><span class="nx">value</span><span class="p">);</span></div><div class='line' id='LC33'>			<span class="p">}</span></div><div class='line' id='LC34'>		<span class="p">});</span></div><div class='line' id='LC35'>	<span class="p">}</span></div><div class='line' id='LC36'><br/></div><div class='line' id='LC37'>	<span class="kd">function</span> <span class="nx">doneLoading</span><span class="p">()</span> <span class="p">{</span></div><div class='line' id='LC38'>		<span class="kd">var</span> <span class="nx">$proper</span> <span class="o">=</span> <span class="nx">$</span><span class="p">(</span><span class="nx">proper</span><span class="p">),</span></div><div class='line' id='LC39'>			<span class="nx">$broken</span> <span class="o">=</span> <span class="nx">$</span><span class="p">(</span><span class="nx">broken</span><span class="p">);</span></div><div class='line' id='LC40'><br/></div><div class='line' id='LC41'>		<span class="k">if</span> <span class="p">(</span> <span class="nx">deferred</span> <span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC42'>			<span class="k">if</span> <span class="p">(</span> <span class="nx">broken</span><span class="p">.</span><span class="nx">length</span> <span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC43'>				<span class="nx">deferred</span><span class="p">.</span><span class="nx">reject</span><span class="p">(</span> <span class="nx">$images</span><span class="p">,</span> <span class="nx">$proper</span><span class="p">,</span> <span class="nx">$broken</span> <span class="p">);</span></div><div class='line' id='LC44'>			<span class="p">}</span> <span class="k">else</span> <span class="p">{</span></div><div class='line' id='LC45'>				<span class="nx">deferred</span><span class="p">.</span><span class="nx">resolve</span><span class="p">(</span> <span class="nx">$images</span> <span class="p">);</span></div><div class='line' id='LC46'>			<span class="p">}</span></div><div class='line' id='LC47'>		<span class="p">}</span></div><div class='line' id='LC48'><br/></div><div class='line' id='LC49'>		<span class="k">if</span> <span class="p">(</span> <span class="nx">$</span><span class="p">.</span><span class="nx">isFunction</span><span class="p">(</span> <span class="nx">callback</span> <span class="p">)</span> <span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC50'>			<span class="nx">callback</span><span class="p">.</span><span class="nx">call</span><span class="p">(</span> <span class="nx">$this</span><span class="p">,</span> <span class="nx">$images</span><span class="p">,</span> <span class="nx">$proper</span><span class="p">,</span> <span class="nx">$broken</span> <span class="p">);</span></div><div class='line' id='LC51'>		<span class="p">}</span></div><div class='line' id='LC52'>	<span class="p">}</span></div><div class='line' id='LC53'><br/></div><div class='line' id='LC54'>	<span class="kd">function</span> <span class="nx">imgLoadedHandler</span><span class="p">(</span> <span class="nx">event</span> <span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC55'>		<span class="nx">imgLoaded</span><span class="p">(</span> <span class="nx">event</span><span class="p">.</span><span class="nx">target</span><span class="p">,</span> <span class="nx">event</span><span class="p">.</span><span class="nx">type</span> <span class="o">===</span> <span class="s1">&#39;error&#39;</span> <span class="p">);</span></div><div class='line' id='LC56'>	<span class="p">}</span></div><div class='line' id='LC57'><br/></div><div class='line' id='LC58'>	<span class="kd">function</span> <span class="nx">imgLoaded</span><span class="p">(</span> <span class="nx">img</span><span class="p">,</span> <span class="nx">isBroken</span> <span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC59'>		<span class="c1">// don&#39;t proceed if BLANK image, or image is already loaded</span></div><div class='line' id='LC60'>		<span class="k">if</span> <span class="p">(</span> <span class="nx">img</span><span class="p">.</span><span class="nx">src</span> <span class="o">===</span> <span class="nx">BLANK</span> <span class="o">||</span> <span class="nx">$</span><span class="p">.</span><span class="nx">inArray</span><span class="p">(</span> <span class="nx">img</span><span class="p">,</span> <span class="nx">loaded</span> <span class="p">)</span> <span class="o">!==</span> <span class="o">-</span><span class="mi">1</span> <span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC61'>			<span class="k">return</span><span class="p">;</span></div><div class='line' id='LC62'>		<span class="p">}</span></div><div class='line' id='LC63'><br/></div><div class='line' id='LC64'>		<span class="c1">// store element in loaded images array</span></div><div class='line' id='LC65'>		<span class="nx">loaded</span><span class="p">.</span><span class="nx">push</span><span class="p">(</span> <span class="nx">img</span> <span class="p">);</span></div><div class='line' id='LC66'><br/></div><div class='line' id='LC67'>		<span class="c1">// keep track of broken and properly loaded images</span></div><div class='line' id='LC68'>		<span class="k">if</span> <span class="p">(</span> <span class="nx">isBroken</span> <span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC69'>			<span class="nx">broken</span><span class="p">.</span><span class="nx">push</span><span class="p">(</span> <span class="nx">img</span> <span class="p">);</span></div><div class='line' id='LC70'>		<span class="p">}</span> <span class="k">else</span> <span class="p">{</span></div><div class='line' id='LC71'>			<span class="nx">proper</span><span class="p">.</span><span class="nx">push</span><span class="p">(</span> <span class="nx">img</span> <span class="p">);</span></div><div class='line' id='LC72'>		<span class="p">}</span></div><div class='line' id='LC73'><br/></div><div class='line' id='LC74'>		<span class="c1">// cache image and its state for future calls</span></div><div class='line' id='LC75'>		<span class="nx">$</span><span class="p">.</span><span class="nx">data</span><span class="p">(</span> <span class="nx">img</span><span class="p">,</span> <span class="s1">&#39;imagesLoaded&#39;</span><span class="p">,</span> <span class="p">{</span> <span class="nx">isBroken</span><span class="o">:</span> <span class="nx">isBroken</span><span class="p">,</span> <span class="nx">src</span><span class="o">:</span> <span class="nx">img</span><span class="p">.</span><span class="nx">src</span> <span class="p">}</span> <span class="p">);</span></div><div class='line' id='LC76'><br/></div><div class='line' id='LC77'>		<span class="c1">// trigger deferred progress method if present</span></div><div class='line' id='LC78'>		<span class="k">if</span> <span class="p">(</span> <span class="nx">hasNotify</span> <span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC79'>			<span class="nx">deferred</span><span class="p">.</span><span class="nx">notifyWith</span><span class="p">(</span> <span class="nx">$</span><span class="p">(</span><span class="nx">img</span><span class="p">),</span> <span class="p">[</span> <span class="nx">isBroken</span><span class="p">,</span> <span class="nx">$images</span><span class="p">,</span> <span class="nx">$</span><span class="p">(</span><span class="nx">proper</span><span class="p">),</span> <span class="nx">$</span><span class="p">(</span><span class="nx">broken</span><span class="p">)</span> <span class="p">]</span> <span class="p">);</span></div><div class='line' id='LC80'>		<span class="p">}</span></div><div class='line' id='LC81'><br/></div><div class='line' id='LC82'>		<span class="c1">// call doneLoading and clean listeners if all images are loaded</span></div><div class='line' id='LC83'>		<span class="k">if</span> <span class="p">(</span> <span class="nx">$images</span><span class="p">.</span><span class="nx">length</span> <span class="o">===</span> <span class="nx">loaded</span><span class="p">.</span><span class="nx">length</span> <span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC84'>			<span class="nx">setTimeout</span><span class="p">(</span> <span class="nx">doneLoading</span> <span class="p">);</span></div><div class='line' id='LC85'>			<span class="nx">$images</span><span class="p">.</span><span class="nx">unbind</span><span class="p">(</span> <span class="s1">&#39;.imagesLoaded&#39;</span><span class="p">,</span> <span class="nx">imgLoadedHandler</span> <span class="p">);</span></div><div class='line' id='LC86'>		<span class="p">}</span></div><div class='line' id='LC87'>	<span class="p">}</span></div><div class='line' id='LC88'><br/></div><div class='line' id='LC89'>	<span class="c1">// if no images, trigger immediately</span></div><div class='line' id='LC90'>	<span class="k">if</span> <span class="p">(</span> <span class="o">!</span><span class="nx">$images</span><span class="p">.</span><span class="nx">length</span> <span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC91'>		<span class="nx">doneLoading</span><span class="p">();</span></div><div class='line' id='LC92'>	<span class="p">}</span> <span class="k">else</span> <span class="p">{</span></div><div class='line' id='LC93'>		<span class="nx">$images</span><span class="p">.</span><span class="nx">bind</span><span class="p">(</span> <span class="s1">&#39;load.imagesLoaded error.imagesLoaded&#39;</span><span class="p">,</span> <span class="nx">imgLoadedHandler</span> <span class="p">)</span></div><div class='line' id='LC94'>		<span class="p">.</span><span class="nx">each</span><span class="p">(</span> <span class="kd">function</span><span class="p">(</span> <span class="nx">i</span><span class="p">,</span> <span class="nx">el</span> <span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC95'>			<span class="kd">var</span> <span class="nx">src</span> <span class="o">=</span> <span class="nx">el</span><span class="p">.</span><span class="nx">src</span><span class="p">;</span></div><div class='line' id='LC96'><br/></div><div class='line' id='LC97'>			<span class="c1">// find out if this image has been already checked for status</span></div><div class='line' id='LC98'>			<span class="c1">// if it was, and src has not changed, call imgLoaded on it</span></div><div class='line' id='LC99'>			<span class="kd">var</span> <span class="nx">cached</span> <span class="o">=</span> <span class="nx">$</span><span class="p">.</span><span class="nx">data</span><span class="p">(</span> <span class="nx">el</span><span class="p">,</span> <span class="s1">&#39;imagesLoaded&#39;</span> <span class="p">);</span></div><div class='line' id='LC100'>			<span class="k">if</span> <span class="p">(</span> <span class="nx">cached</span> <span class="o">&amp;&amp;</span> <span class="nx">cached</span><span class="p">.</span><span class="nx">src</span> <span class="o">===</span> <span class="nx">src</span> <span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC101'>				<span class="nx">imgLoaded</span><span class="p">(</span> <span class="nx">el</span><span class="p">,</span> <span class="nx">cached</span><span class="p">.</span><span class="nx">isBroken</span> <span class="p">);</span></div><div class='line' id='LC102'>				<span class="k">return</span><span class="p">;</span></div><div class='line' id='LC103'>			<span class="p">}</span></div><div class='line' id='LC104'><br/></div><div class='line' id='LC105'>			<span class="c1">// if complete is true and browser supports natural sizes, try</span></div><div class='line' id='LC106'>			<span class="c1">// to check for image status manually</span></div><div class='line' id='LC107'>			<span class="k">if</span> <span class="p">(</span> <span class="nx">el</span><span class="p">.</span><span class="nx">complete</span> <span class="o">&amp;&amp;</span> <span class="nx">el</span><span class="p">.</span><span class="nx">naturalWidth</span> <span class="o">!==</span> <span class="kc">undefined</span> <span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC108'>				<span class="nx">imgLoaded</span><span class="p">(</span> <span class="nx">el</span><span class="p">,</span> <span class="nx">el</span><span class="p">.</span><span class="nx">naturalWidth</span> <span class="o">===</span> <span class="mi">0</span> <span class="o">||</span> <span class="nx">el</span><span class="p">.</span><span class="nx">naturalHeight</span> <span class="o">===</span> <span class="mi">0</span> <span class="p">);</span></div><div class='line' id='LC109'>				<span class="k">return</span><span class="p">;</span></div><div class='line' id='LC110'>			<span class="p">}</span></div><div class='line' id='LC111'><br/></div><div class='line' id='LC112'>			<span class="c1">// cached images don&#39;t fire load sometimes, so we reset src, but only when</span></div><div class='line' id='LC113'>			<span class="c1">// dealing with IE, or image is complete (loaded) and failed manual check</span></div><div class='line' id='LC114'>			<span class="c1">// webkit hack from http://groups.google.com/group/jquery-dev/browse_thread/thread/eee6ab7b2da50e1f</span></div><div class='line' id='LC115'>			<span class="k">if</span> <span class="p">(</span> <span class="nx">el</span><span class="p">.</span><span class="nx">readyState</span> <span class="o">||</span> <span class="nx">el</span><span class="p">.</span><span class="nx">complete</span> <span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC116'>				<span class="nx">el</span><span class="p">.</span><span class="nx">src</span> <span class="o">=</span> <span class="nx">BLANK</span><span class="p">;</span></div><div class='line' id='LC117'>				<span class="nx">el</span><span class="p">.</span><span class="nx">src</span> <span class="o">=</span> <span class="nx">src</span><span class="p">;</span></div><div class='line' id='LC118'>			<span class="p">}</span></div><div class='line' id='LC119'>		<span class="p">});</span></div><div class='line' id='LC120'>	<span class="p">}</span></div><div class='line' id='LC121'><br/></div><div class='line' id='LC122'>	<span class="k">return</span> <span class="nx">deferred</span> <span class="o">?</span> <span class="nx">deferred</span><span class="p">.</span><span class="nx">promise</span><span class="p">(</span> <span class="nx">$this</span> <span class="p">)</span> <span class="o">:</span> <span class="nx">$this</span><span class="p">;</span></div><div class='line' id='LC123'><span class="p">};</span></div><div class='line' id='LC124'><br/></div><div class='line' id='LC125'><span class="p">})(</span><span class="nx">jQuery</span><span class="p">);</span></div></pre></div>
            </td>
          </tr>
        </table>
  </div>

  </div>
</div>

<a href="#jump-to-line" rel="facebox[.linejump]" data-hotkey="l" class="js-jump-to-line" style="display:none">Jump to Line</a>
<div id="jump-to-line" style="display:none">
  <form accept-charset="UTF-8" class="js-jump-to-line-form">
    <input class="linejump-input js-jump-to-line-field" type="text" placeholder="Jump to line&hellip;" autofocus>
    <button type="submit" class="button">Go</button>
  </form>
</div>

        </div>

      </div><!-- /.repo-container -->
      <div class="modal-backdrop"></div>
    </div><!-- /.container -->
  </div><!-- /.site -->


    </div><!-- /.wrapper -->

      <div class="container">
  <div class="site-footer">
    <ul class="site-footer-links right">
      <li><a href="https://status.github.com/">Status</a></li>
      <li><a href="http://developer.github.com">API</a></li>
      <li><a href="http://training.github.com">Training</a></li>
      <li><a href="http://shop.github.com">Shop</a></li>
      <li><a href="/blog">Blog</a></li>
      <li><a href="/about">About</a></li>

    </ul>

    <a href="/">
      <span class="mega-octicon octicon-mark-github"></span>
    </a>

    <ul class="site-footer-links">
      <li>&copy; 2013 <span title="0.03750s from github-fe125-cp1-prd.iad.github.net">GitHub</span>, Inc.</li>
        <li><a href="/site/terms">Terms</a></li>
        <li><a href="/site/privacy">Privacy</a></li>
        <li><a href="/security">Security</a></li>
        <li><a href="/contact">Contact</a></li>
    </ul>
  </div><!-- /.site-footer -->
</div><!-- /.container -->


    <div class="fullscreen-overlay js-fullscreen-overlay" id="fullscreen_overlay">
  <div class="fullscreen-container js-fullscreen-container">
    <div class="textarea-wrap">
      <textarea name="fullscreen-contents" id="fullscreen-contents" class="js-fullscreen-contents" placeholder="" data-suggester="fullscreen_suggester"></textarea>
          <div class="suggester-container">
              <div class="suggester fullscreen-suggester js-navigation-container" id="fullscreen_suggester"
                 data-url="/desandro/imagesloaded/suggestions/commit">
              </div>
          </div>
    </div>
  </div>
  <div class="fullscreen-sidebar">
    <a href="#" class="exit-fullscreen js-exit-fullscreen tooltipped leftwards" title="Exit Zen Mode">
      <span class="mega-octicon octicon-screen-normal"></span>
    </a>
    <a href="#" class="theme-switcher js-theme-switcher tooltipped leftwards"
      title="Switch themes">
      <span class="octicon octicon-color-mode"></span>
    </a>
  </div>
</div>



    <div id="ajax-error-message" class="flash flash-error">
      <span class="octicon octicon-alert"></span>
      <a href="#" class="octicon octicon-remove-close close ajax-error-dismiss"></a>
      Something went wrong with that request. Please try again.
    </div>

    
  </body>
</html>

