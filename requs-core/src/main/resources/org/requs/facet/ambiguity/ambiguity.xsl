<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns="http://www.w3.org/1999/xhtml" version="1.0">
    <xsl:include href="layout.xsl"/>
    <xsl:template name="head">
        <title>ambiguity</title>
    </xsl:template>
    <xsl:template name="body">
        <h1><xsl:text>Ambiguity Metrics</xsl:text></h1>
        <ul>
            <xsl:apply-templates select="/metrics/metric"/>
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
