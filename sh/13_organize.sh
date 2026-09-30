#!/bin/sh
# 13 — Organize a messy folder by file type
#
# GOAL     sh 13_organize.sh DIR           DRY RUN: only print what it WOULD do
#          sh 13_organize.sh DIR --doit    actually move the files
#
#              images/  ← jpg jpeg png gif webp
#              docs/    ← pdf txt md docx
#              audio/   ← mp3 flac wav ogg
#              video/   ← mp4 mkv webm
#              archives/← zip tar gz xz zst 7z
#              other/   ← everything else, including files with no extension
#
#          Never overwrite. If images/a.jpg already exists, skip it and
#          say so.
#
# PRACTICE ON A SANDBOX FIRST, not on ~/Downloads:
#          mkdir -p ~/learn/sandbox && cd ~/learn/sandbox &&
#          touch a.JPG b.pdf "c d.mp3" e.tar.gz README .hidden x.webm
#
# CHECK    ls -R DIR    before and after. Run it twice. The second run
#          should do nothing.
#
# HINTS
#   H1  ${f##*.} is the extension ("everything after the last dot"). What
#       does it give for "README"? For "e.tar.gz"? Test in your shell first.
#   H2  case "$ext" in jpg|jpeg|png) cat=images ;; ... esac  (lowercase the
#       ext first: tr '[:upper:]' '[:lower:]')
#   H3  Only move regular files: [ -f "$f" ] || continue. Otherwise
#       images/ would get sorted into other/ on the second run.
#   H4  mv -n refuses to overwrite, but it won't tell you it skipped.
#       Check [ -e "$dest" ] yourself and print a message.
#   H5  Dry run: build the command, then either echo it or run it.
#       A variable like run="echo" (dry) or run="" (--doit) does the trick,
#       then  $run mv ...  — do you see why this is a little fragile?
#   H6  Hidden files (.hidden) don't match *. Should they be moved at all?

set -eu

dir="${1:-}"
[ -d "$dir" ] || { echo "usage: $0 DIR [--doit]" >&2; exit 2; }
doit=no
[ "${2:-}" = "--doit" ] && doit=yes

# prints the category for one filename
category() {
    # TODO: extension → lowercase → case → echo the folder name
    echo other
}

for f in "$dir"/*; do
    # TODO: skip non-regular files
    # TODO: dest = "$dir/$(category "$f")/<basename>"
    # TODO: exists → "skip:" message ; else dry-run print or mkdir -p + mv
    :
done

[ "$doit" = yes ] || echo "(dry run — add --doit to move files)"
