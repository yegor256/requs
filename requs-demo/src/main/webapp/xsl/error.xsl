<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns="http://www.w3.org/1999/xhtml" version="2.0">
    <xsl:output method="xml" omit-xml-declaration="yes"/>
    <xsl:include href="/xsl/layout.xsl"/>
    <xsl:template match="page" mode="head">
        <title>
            <xsl:text>error</xsl:text>
        </title>
    </xsl:template>
    <xsl:template match="page" mode="body">
        <h1>
            <xsl:text>Page not found</xsl:text>
        </h1>
        <p>
            <xsl:text>Invalid request or page not found.</xsl:text>
        </p>
    </xsl:template>
</xsl:stylesheet>
