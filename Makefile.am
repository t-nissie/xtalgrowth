# Makefile.am for xtalgrowth
# Process this file with automake to create Makefile.in
# Time-stamp: <2009-10-06 17:19:43 takeshi>
# Author: Takeshi NISHIMATSU
##
AUTOMAKE_OPTIONS = foreign
SUBDIRS = src
EXTRA_DIST = README-ja README-ja.html COPYING figures style.css favicon.ico
CLEANFILES = *.html
SNAPSHOT_NAME=$(PACKAGE)-$(VERSION)_`date +"%Y-%m-%d_%H"`
SOURCEFORGE_XTALGROWTH=web.sourceforge.net:/home/groups/l/lo/loto/htdocs/xtalgrowth

sf: sourceforge
sourceforge: README-ja.html README-ja style.css COPYING favicon.ico
	scp $<         $(SOURCEFORGE_XTALGROWTH)/index.html
	scp $<         $(SOURCEFORGE_XTALGROWTH)/index-ja.html
	scp $^         $(SOURCEFORGE_XTALGROWTH)
	scp -r figures $(SOURCEFORGE_XTALGROWTH)

README-ja.html:  README-ja
	ruby -I $(srcdir) $< $< > $@

dist-hook:
	rm -rf `find $(distdir) -type d -name .svn`

.PHONY: snapshot
snapshot:
	$(MAKE) dist distdir=$(SNAPSHOT_NAME)
	mpack -s $(SNAPSHOT_NAME).tar.gz $(SNAPSHOT_NAME).tar.gz t_nissie@yahoo.co.jp
