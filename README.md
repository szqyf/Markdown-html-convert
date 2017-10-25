# Markdown-html-convert
convert markerdown to html

## 目前主要设计想法：
1. 分三个模块：
- Main 主控模块，负责CLI的接入，生成对应的Parser和Render来完成工作
_ GFM 模块，提供GitHub Flavored Markdown语言的Parser和Render(暂未安排)
- HTML 模块，提供HTML语言的Parser(暂未安排)和Parser

2. 类结构：
- IParser 解析接口
```c++    
    const AstNode &from(std::istream &in);
    const AstNode parse_from_line(std::stream &in);
    const AstNode document() const;
```

- IRender 渲染接口（暂未定义）

- Ast 数据节点交换类  
  包含 AstNode = std::shared_ptr<Ast>  
       Asts = std::vector<AstNode>  
  两类

3. 一些辅助函数：
- ts::make_parser 生成解析实体
- ts::make_render 生成渲染实体
- 重载 << >> 符号，实现istream, ostream 流的操作