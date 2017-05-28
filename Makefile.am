# Makefile.am for xtalgrowth
# Process this file with automake to create Makefile.in
# Time-stamp: <2017-05-28 21:26:54 takeshi>
# Author: Takeshi NISHIMATSU
##
SUBDIRS = src
EXTRA_DIST = index.en.html index.es.html index.ja.html README COPYING figures style.css favicon.ico
SNAPSHOT_NAME=$(PACKAGE)-$(VERSION)_`date +"%Y-%m-%d_%H"`
SOURCEFORGE_XTALGROWTH=web.sourceforge.net:/home/groups/l/lo/loto/htdocs/xtalgrowth
man1_MANS = xtalgrowth.1

sf: sourceforge
sourceforge: index.en.html index.es.html index.ja.html README index.var style.css COPYING favicon.ico dot.htaccess
	scp $<             $(SOURCEFORGE_XTALGROWTH)/index.html
	scp dot.htaccess   $(SOURCEFORGE_XTALGROWTH)/.htaccess
	scp $^             $(SOURCEFORGE_XTALGROWTH)
########scp -r figures     $(SOURCEFORGE_XTALGROWTH)

dist-hook:
	rm -rf `find $(distdir) -type d -name .svn`

.PHONY: snapshot
snapshot:
	$(MAKE) dist distdir=$(SNAPSHOT_NAME)
	mpack -s $(SNAPSHOT_NAME).tar.gz $(SNAPSHOT_NAME).tar.gz t_nissie@yahoo.co.jp
