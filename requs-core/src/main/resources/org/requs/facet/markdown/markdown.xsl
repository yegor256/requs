<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns="http://www.w3.org/1999/xhtml" version="1.0">
    <xsl:include href="layout.xsl"/>
    <xsl:template name="head">
        <title>markdown</title>
    </xsl:template>
    <xsl:template name="body">
        <xsl:apply-templates select="pages/methods/method"/>
    </xsl:template>
    <xsl:template match="method">
        <h1><xsl:value-of select="@id"/></h1>
        <div>
            <xsl:value-of select="html" disable-output-escaping="yes"/>
        </div>
    </xsl:template>
</xsl:stylesheet>
