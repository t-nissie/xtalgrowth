# Makefile.am for xtalgrowth
# Process this file with automake to create Makefile.in
# Time-stamp: <2023-12-24 18:05:57 takeshi>
# Author: Takeshi NISHIMATSU
##
SUBDIRS = src
man_MANS = xtalgrowth.1
EXTRA_DIST = index.en.html index.es.html index.ja.html COPYING figures style.css favicon.ico\
             CMakeLists.txt ChangeLog.md $(man_MANS)
SOURCEFORGE_XTALGROWTH=web.sourceforge.net:/home/groups/l/lo/loto/htdocs/xtalgrowth

sf: sourceforge
sourceforge: index.en.html index.es.html index.ja.html README.md index.var style.css COPYING favicon.ico dot.htaccess
	scp $<             $(SOURCEFORGE_XTALGROWTH)/index.html
	scp dot.htaccess   $(SOURCEFORGE_XTALGROWTH)/.htaccess
	scp $^             $(SOURCEFORGE_XTALGROWTH)

dist-hook:
	rm -rf `find $(distdir) -type d -name .svn`

cmakecheck: CMakeLists.txt   # It checks CMakeLists.txt and src/CMakeLists.txt.in. It works only in-source.
	mkdir -p CMakeCheckBuild
	cd       CMakeCheckBuild ; \
	cmake -G Ninja .. ; \
	ninja clean ; \
	ninja ; \
	src/xtalgrowth --version ; \
	ninja clean
	rm -r    CMakeCheckBuild
