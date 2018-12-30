#!/bin/bash

assetPath=/Users/srikanthsh/src/freshworks-website-prototypes/2017-freshworks/assets-collection
cd $assetPath
# echo $assets
assets="$(ls -R assets/fonts | awk '
/:$/&&f{s=$0;f=0}
/:$/&&!f{sub(/:$/,"");s=$0;f=1;next}
NF&&f{ print s"/"$0 }')"
echo "$assets"