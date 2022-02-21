if exists('g:loaded_markshown') | finish | endif " prevent loading file twice

let s:save_cpo = &cpo " save user coptions
set cpo&vim " reset them to defaults

" command to run out plugin
command! Markshown lua require'markshown'.markshown()

let &cpo = s:save_cpo " and restore after
unlet s:save_cpo

let g:loaded_markshown = 1
