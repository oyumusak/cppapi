#!/bin/bash

rm -rf ./.Trash/*;
rm -rf ./.cache/*;
rm -rf ./Library/Caches/*;
rm -rf ./Library/Containers/com.docker.docker/*;
rm -rf ./Library/Containers/*;
rm -rf ./Library/Application Support/Code/User/*;
rm -rf ./Library/Application Support/Code/CachedData/*;
rm -rf ./Library/Developer/CoreSimulator/*;
/bin/rm -rf "$HOME"/Library/*.42* &>/dev/null
/bin/rm -rf "$HOME"/*.42* &>/dev/null
/bin/rm -rf "$HOME"/.zcompdump* &>/dev/null
/bin/rm -rf "$HOME"/.cocoapods.42_cache_bak* &>/dev/null
/bin/chmod -R 777 "$HOME"/Library/Caches/Homebrew &>/dev/null
/bin/rm -rf "$HOME"/Library/Caches/* &>/dev/null
/bin/rm -rf "$HOME"/Library/Application\ Support/Caches/* &>/dev/null
/bin/rm -rf "$HOME"/Library/Application\ Support/Slack/Service\ Worker/CacheStorage/* &>/dev/null
/bin/rm -rf "$HOME"/Library/Application\ Support/Slack/Cache/* &>/dev/null
/bin/rm -rf "$HOME"/Library/Application\ Support/discord/Cache/* &>/dev/null
/bin/rm -rf "$HOME"/Library/Application\ Support/discord/Code\ Cache/js* &>/dev/null
/bin/rm -rf "$HOME"/Library/Application\ Support/discord/Crashpad/completed/*  &>/dev/null
/bin/rm -rf "$HOME"/Library/Application\ Support/Code/Cache/* &>/dev/null
/bin/rm -rf "$HOME"/Library/Application\ Support/Code/CachedData/* &>/dev/null
/bin/rm -rf "$HOME"/Library/Application\ Support/Code/Crashpad/completed/* &>/dev/null
/bin/rm -rf "$HOME"/Library/Application\ Support/Code/User/workspaceStorage/* &>/dev/null
/bin/rm -rf "$HOME"/Library/Application\ Support/Google/Chrome/Profile\ [0-9]/Service\ Worker/CacheStorage/* &>/dev/null
/bin/rm -rf "$HOME"/Library/Application\ Support/Google/Chrome/Default/Service\ Worker/CacheStorage/* &>/dev/null
/bin/rm -rf "$HOME"/Library/Application\ Support/Google/Chrome/Profile\ [0-9]/Application\ Cache/* &>/dev/null
/bin/rm -rf "$HOME"/Library/Application\ Support/Google/Chrome/Default/Application\ Cache/* &>/dev/null
/bin/rm -rf "$HOME"/Library/Application\ Support/Google/Chrome/Crashpad/completed/* &>/dev/null
/bin/rm -rf "$HOME"/Library/Application\ Support/Chromium/Default/File\ System &>/dev/null
/bin/rm -rf "$HOME"/Library/Application\ Support/Chromium/Profile\ [0-9]/File\ System &>/dev/null
/bin/rm -rf "$HOME"/Library/Application\ Support/Google/Chrome/Default/File\ System &>/dev/null
/bin/rm -rf "$HOME"/Library/Application\ Support/Google/Chrome/Profile\ [0-9]/File\ System &>/dev/null
/bin/rm -rf "$HOME"/Desktop/Piscine\ Rules\ *.mp4
/bin/rm -rf "$HOME"/Desktop/PLAY_ME.webloc
find "$HOME"/Desktop -name .DS_Store -depth -exec /bin/rm {} \; &>/dev/null