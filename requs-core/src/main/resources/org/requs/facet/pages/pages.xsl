<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns="http://www.w3.org/1999/xhtml" version="1.0">
    <xsl:include href="layout.xsl"/>
    <xsl:template name="head">
        <title>pages</title>
    </xsl:template>
    <xsl:template name="body">
        <h1>
            <xsl:text>Pages</xsl:text>
        </h1>
        <ul>
            <xsl:apply-templates select="pages/page"/>
        </ul>
    </xsl:template>
    <xsl:template match="page">
        <li>
            <a>
                <xsl:attribute name="href">
                    <xsl:text>pages/</xsl:text>
                    <xsl:value-of select="title"/>
                    <xsl:text>.html</xsl:text>
                </xsl:attribute>
                <xsl:value-of select="title"/>
            </a>
        </li>
    </xsl:template>
</xsl:stylesheet>
