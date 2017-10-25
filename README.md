**MustacheC++**
-----------
This is my second attempt at implementing the mustache template language

I will be taking references from


https://mustache.github.io/mustache.5.html - Language description
https://mustache.github.io/mustache.1.html - Command line interface
https://github.com/janl/mustache.js/ - Implementation in Js with extra features

Steps to accomplish:

 1. Lexer 
	Create list of tokens
        - Text
        - Tag Analyse the tag for "Set Delimiter" which is a special tag that allows the user to change the tag delimiters
            {{=<% %>=}} <- new delimiters <% %>

 2. Parser 
	 Create abstract syntax tree from tokens list
         Types of tags
            - Variables
                {{name}}
                HTML escaped by default (Possible implementation https://stackoverflow.com/questions/5665231/most-efficient-way-to-escape-xml-html-in-c-string)
                {{{name}}} (note 3 { and }) or {{& name}} to show unescaped HTML
                Null values can be represented as an empty string or maybe add a way to throw an exception
            - Section
                start {{#name}}
                end {{/name}}
                Can be multiple things:
                - False Values or Empty Lists
                - Non-Empty Lists
                - Lambdas
                - Non-False Values
            - Inverted Sections
                start {{^name}}
                end {{/name}}
            - Comments
                {{! ignore me }}
            - Partials
                {{> next_more}} = next_more.mustache <- Rendered at runtime

 3. Evaluator
	Produce final output


