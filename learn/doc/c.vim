
" Add to :/usr/share/vim/vim73/syntax/c.vim
"Highlight Functions
syn match cFunctions display "[a-zA-Z_]\{-1,}\s\{-0,}(\{1}"ms=s,me=e-1
hi cFunctions ctermfg=lightcyan cterm=BOLD
"hi cFunctions ctermfg=lightred ctermbg=lightgreen cterm=BOLD
"hi def link cFunctions ctermfg=lightred cterm=BOLD
