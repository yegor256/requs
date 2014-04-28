<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns="http://www.w3.org/1999/xhtml" version="1.0">
    <xsl:include href="layout.xsl"/>
    <xsl:template name="head">
        <title>index</title>
        <style type="text/css">
            body { margin: 2em; font-family: Ubuntu; font-size: 16px; }
            a { color: #428bca; text-decoration: none; }
            a:hover { text-decoration: underline; }
        </style>
    </xsl:template>
    <xsl:template name="body">
        <xsl:apply-templates select="/index/facets"/>
    </xsl:template>
    <xsl:template match="facets">
        <h1>Facets</h1>
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
                    <xsl:value-of select="@id"/>
                </a>
            </td>
            <td><xsl:value-of select="description"/></td>
        </tr>
    </xsl:template>
</xsl:stylesheet>
