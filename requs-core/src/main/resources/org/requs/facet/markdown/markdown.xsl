<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns="http://www.w3.org/1999/xhtml" version="2.0"
    exclude-result-prefixes="xs">
    <xsl:output method="xml"/>
    <xsl:strip-space elements="*" />
    <xsl:template match="/">
        <html lang="en">
            <head>
                <title>markdown</title>
                <meta name="description" content="markdown"/>
                <meta name="keywords" content="software requirements specification"/>
                <meta name="author" content="requs"/>
                <meta name="viewport" content="width=device-width, initial-scale=1.0" />
                <style type="text/css">
                    body { margin: 2em; font-family: Ubuntu; font-size: 16px; }
                    a { color: #428bca; text-decoration: none; }
                    a:hover { text-decoration: underline; }
                </style>
                <script type="text/javascript">
                    function show(name) {
                        alert("This feature doesn't work yet. Check the file manually: " + name);
                    }
                </script>
            </head>
            <body>
                <xsl:apply-templates select="methods"/>
            </body>
        </html>
    </xsl:template>
    <xsl:template match="methods">
        <ul>
            <xsl:apply-templates select="method"/>
        </ul>
    </xsl:template>
    <xsl:template match="method">
        <li>
            <span>
                <xsl:attribute name="onclick">
                    <xsl:text>show('</xsl:text>
                    <xsl:value-of select="."/>
                    <xsl:text>');</xsl:text>
                </xsl:attribute>
                <xsl:value-of select="@id"/>
            </span>
        </li>
    </xsl:template>
</xsl:stylesheet>
