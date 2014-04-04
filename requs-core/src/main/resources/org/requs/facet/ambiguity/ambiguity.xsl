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
                <title>ambiguity</title>
                <meta name="description" content="ambiguity metrics"/>
                <meta name="keywords" content="software requirements specification"/>
                <meta name="author" content="requs"/>
                <meta name="viewport" content="width=device-width, initial-scale=1.0" />
                <style type="text/css">
                    body { margin: 2em; font-family: Ubuntu; font-size: 16px; }
                    a { color: #428bca; text-decoration: none; }
                    a:hover { text-decoration: underline; }
                </style>
            </head>
            <body>
                <xsl:apply-templates select="/metrics"/>
            </body>
        </html>
    </xsl:template>
    <xsl:template match="metrics">
        <ul>
            <xsl:apply-templates select="metric"/>
        </ul>
    </xsl:template>
    <xsl:template match="metric">
        <li>
            <xsl:value-of select="@id"/>
            <xsl:text>: </xsl:text>
            <xsl:value-of select="."/>
        </li>
    </xsl:template>
</xsl:stylesheet>
