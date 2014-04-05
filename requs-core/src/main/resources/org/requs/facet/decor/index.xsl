<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns="http://www.w3.org/1999/xhtml" version="2.0"
    exclude-result-prefixes="xs">
    <xsl:output method="xml" omit-xml-declaration="yes"/>
    <xsl:strip-space elements="*"/>
    <xsl:template match="/">
        <html lang="en">
            <head>
                <title>index</title>
                <meta name="description" content="index"/>
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
                <xsl:apply-templates select="index/facets"/>
            </body>
        </html>
    </xsl:template>
    <xsl:template match="facets">
        <table>
            <thead>
                <tr>
                    <th><xsl:text>Name</xsl:text></th>
                    <th><xsl:text>Description</xsl:text></th>
                </tr>
            </thead>
            <tbody>
                <xsl:apply-templates select="facet"/>
            </tbody>
        </table>
    </xsl:template>
    <xsl:template match="facet">
        <tr>
            <td>
                <a>
                    <xsl:attribute name="href">
                        <xsl:value-of select="file"/>
                    </xsl:attribute>
                    <xsl:value-of select="name"/>
                </a>
            </td>
            <td><xsl:value-of select="description"/></td>
        </tr>
    </xsl:template>
</xsl:stylesheet>
