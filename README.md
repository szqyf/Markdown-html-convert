# Markdown-html-convert
convert markerdown to html

## 目前主要设计想法：
1. 有三个基类：
    * Syntax  
    语法类：尝试提炼语法的共同点，看是否能使用共同的基类来展示，考虑从配置文件中获取；
    * IParser  
    解析类：解析文本，生成Syntax树；
    * IRender  
    渲染类：实现将Syntax树重新生成文本，可考虑从配置文件中获取生成方式。

2. Parser类，按字符读取数据并投入现有的vector<Syntax>中进行判断？还是按行读取投入？  
    伪代码如下：
    ```c++
    static const vector<Syntax> Syntaxes;

    tree<Token> read_from_stream(stream s) {
        string buff = "";
        char ch;
        tree ret;

        while ((ch = s.read()) != eof) {
            buff += ch;

            for (auto syn: Syntaxes) {
                if (syn.is(buff)) {
                    ret.add_leaf(syn.handle_stream(buff, s));
                    buff = "";
                    break;
                }
            }
        }

        return std::move(ret);
    }
    ```

3. 