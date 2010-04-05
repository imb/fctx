"""Builds the download page based on the released files.

This is just a little helper to execute after building all the release files. It will generate the contents of a wiki page that I can upload to wildbear to finish off a release.
"""

import hashlib
import sys

RELEASE_LISTING = [
    'fct.h',
    'fctx-doc-%(ver)s.tar.gz',
    'fctx-src-%(ver)s.tar.gz',
    'patch-%(ver)s.gz',
    'README',
    'NEWS-%(ver)s',
    'diffstat-%(ver)s',
    'ChangeLog-%(ver)s'
]

fname_args = {'ver':sys.argv[1]}

print "== %(ver)s (Stable) ==" % (fname_args)
print "||<tablestyle=\"float:right;margin:2em;\">'''Files''' ||<:>'''md5'''||"

for l in RELEASE_LISTING:
    m = hashlib.md5()
    fname = l % (fname_args)
    m.update(open(fname).read())
    digest = m.hexdigest()
    print "|| [[http://fctx.wildbearsoftware.com/static/fctx/download/%s|%s]] ||  %s ||" % (fname,digest)

print
print
print "=== Release Notes ==="
print
release_lines = open("NEWS").readlines()
notes = []
start_parse = False
for line in release_lines:
    # First underline in first release note section
    if line.find(sys.argv[1]) >= 0:
        start_parse = True
    elif line.startswith("Whats"):
        start_parse = False
    elif start_parse and not line.startswith("-----"):
        notes.append(line)

print "".join(notes)
