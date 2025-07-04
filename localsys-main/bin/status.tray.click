#!/bin/bash

test -f ~/.local/var/status.tray.freeze && trash ~/.local/var/status.tray.freeze && exit
touch ~/.local/var/status.tray.freeze
