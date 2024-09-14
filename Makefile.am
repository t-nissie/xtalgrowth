# Makefile.am for xtalgrowth
# Process this file with automake to create Makefile.in
# Time-stamp: <2024-09-14 22:11:18 takeshi>
# Author: Takeshi NISHIMATSU
##
SUBDIRS = src
man_MANS = xtalgrowth.1
docfiguresdir = $(docdir)/figures
dist_doc_DATA = index.en.html index.es.html index.ja.html COPYING style.css favicon.ico README.md
EXTRA_DIST =    index.en.html index.es.html index.ja.html COPYING style.css favicon.ico figures\
             CMakeLists.txt ChangeLog.md $(man_MANS)
dist_docfigures_DATA = figures/cd.jpg figures/example.jpg figures/large.jpg figures/xtals.jpg
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
