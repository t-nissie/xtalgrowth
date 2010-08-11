# Makefile.am for xtalgrowth
# Process this file with automake to create Makefile.in
# Time-stamp: <2010-08-11 16:43:43 takeshi>
# Author: Takeshi NISHIMATSU
##
AUTOMAKE_OPTIONS = foreign
SUBDIRS = src
EXTRA_DIST = README.ja index.ja.html README.en index.en.html COPYING figures style.css favicon.ico
SNAPSHOT_NAME=$(PACKAGE)-$(VERSION)_`date +"%Y-%m-%d_%H"`
SOURCEFORGE_XTALGROWTH=web.sourceforge.net:/home/groups/l/lo/loto/htdocs/xtalgrowth

sf: sourceforge
sourceforge: index.en.html README.en index.ja.html README.ja index.var style.css COPYING favicon.ico dot.htaccess
	scp $<             $(SOURCEFORGE_XTALGROWTH)/index.html
	scp dot.htaccess   $(SOURCEFORGE_XTALGROWTH)/.htaccess
	scp $^             $(SOURCEFORGE_XTALGROWTH)
########scp -r figures     $(SOURCEFORGE_XTALGROWTH)

index.%.html: README.%
	ruby $< $< | sed -e 's%</h1>%</h1><div class="navi">[<a href="index.en.html">English</a>/<a href="index.ja.html">Japanese</a>]</div>%' > $@

dist-hook:
	rm -rf `find $(distdir) -type d -name .svn`

.PHONY: snapshot
snapshot:
	$(MAKE) dist distdir=$(SNAPSHOT_NAME)
	mpack -s $(SNAPSHOT_NAME).tar.gz $(SNAPSHOT_NAME).tar.gz t_nissie@yahoo.co.jp
