<?xml version="1.0"?>
<!--
 * Copyright (c) 2011-2012, ReXSL.com
 * All rights reserved.
 -->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns="http://www.w3.org/1999/xhtml" version="2.0" exclude-result-prefixes="xs">
    <xsl:output method="xml" omit-xml-declaration="yes"/>
    <xsl:include href="/xsl/layout.xsl"/>
    <xsl:template name="head">
        <title>
            <xsl:text>error</xsl:text>
        </title>
    </xsl:template>
    <xsl:template name="content">
        <h1>
            <xsl:text>Page not found</xsl:text>
        </h1>
        <p>
            <xsl:text>Invalid request or page not found.</xsl:text>
        </p>
    </xsl:template>
</xsl:stylesheet>
