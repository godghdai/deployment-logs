安装依赖 [https://github.com/jonschlinkert/markdown-toc](https://github.com/jonschlinkert/markdown-toc)
```shell
npm install --save markdown-toc
```

假设你需要生成的文档为此目录下的README.md
```
npx markdown-toc README.md
```

```shell
Usage: markdown-toc [options] <input>

  input:        The Markdown file to parse for table of contents,
                or "-" to read from stdin.

  -i:           Edit the <input> file directly, injecting the TOC at <!-- toc -->;
                (Without this flag, the default is to print the TOC to stdout.)

  --json:       Print the TOC in JSON format

  --append:     Append a string to the end of the TOC

  --bullets:    Bullets to use for items in the generated TOC
                (Supports multiple bullets: --bullets "*" --bullets "-" --bullets "+")
                (Default is "*".)

  --maxdepth:   Use headings whose depth is at most maxdepth
                (Default is 6.)

  --no-firsth1: Include the first h1-level heading in a file

  --no-stripHeadingTags: Do not strip extraneous HTML tags from heading
                         text before slugifying
```
