# 安装vim插件


## 安装插件总管

`git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim`

在`~/.vimrc`中添加如下代码
```
set nocompatible              " be iMproved, required
filetype off
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
Plugin 'VundleVim/Vundle.vim'
Plugin 'fatih/vim-go'
Plugin 'Valloric/YouCompleteMe'
Plugin 'Lokaltog/vim-powerline'
Plugin 'scrooloose/nerdtree'
Plugin 'Yggdroot/indentLine'
call vundle#end()
filetype plugin indent on
```


## 安装vim-go

在`~/.vimrc` 中添加如下代码

```
call plug#begin()

" ....

call plug#end()
```
之间添加`Plugin 'fatih/vim-go'`

退出，再打开vim，执行 `:PluginInstall`


# 安装yourcompleteme

如上
```Plug 'Valloric/YouCompleteMe'```

再`:PlugInstall`

重启vim，输入指令重启ycm服务器 `:YcmRestartServer`

编译的命令：
```
cd ~/.vim/bundle/YouCompleteMe
./install.py --clang-completer
```

参数 --clang-completer是为了加上C系列语言的自动补全，如果不需要可以不加


```
" 解决 No .ycm_extra_conf.py detected
let g:ycm_global_ycm_extra_conf = "~/.vim/bundle/YouCompleteMe/third_party/ycmd/.ycm_extra_conf.py"

" 设置回车为补全确认键
let g:ycm_key_list_stop_completion = ['<CR>']
```



## 安装vim-powerline
```Plugin 'Lokaltog/vim-powerline'```

```
set laststatus=2   " Always show the statusline
set encoding=utf-8 " Necessary to show Unicode glyphs
set t_Co=256
let g:Powerline_symbols= 'unicode'
```


## 安装NERDTree

```Plugin 'scrooloose/nerdtree'```

```
" NERDTree 插件的相关配置
"F2开启和关闭树"
map <F2> :NERDTreeToggle<CR>
let NERDTreeChDirMode=1
"显示书签"
let NERDTreeShowBookmarks=1
"设置忽略文件类型"
let NERDTreeIgnore=['\~$', '\.pyc$', '\.swp$']
"窗口大小"
let NERDTreeWinSize=25
```

## 安装indentline

```Plugin 'Yggdroot/indentLine'```


```:echo has("conceal")``` 如果为0表示vim不带conceal功能，就没法用indentline
