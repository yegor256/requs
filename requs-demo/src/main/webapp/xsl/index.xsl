<?xml version="1.0"?>
<!--
 * Copyright (c) 2011-2012, ReXSL.com
 * All rights reserved.
 -->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns="http://www.w3.org/1999/xhtml" version="2.0" exclude-result-prefixes="xs">
    <xsl:output method="xml" omit-xml-declaration="yes"/>
    <xsl:include href="/xsl/layout.xsl"/>
    <xsl:template name="head">
        <script type="text/javascript" src="http://code.jquery.com/jquery-1.11.0.min.js">
            <xsl:text> </xsl:text>
            <!-- this is for W3C compliance -->
        </script>
        <script type="text/javascript" src="js/demo.js">
            <xsl:text> </xsl:text>
            <!-- this is for W3C compliance -->
        </script>
        <title>
            <xsl:text>index</xsl:text>
        </title>
    </xsl:template>
    <xsl:template name="content">
        <div style="float:left; width: 410px;">
            <p style="margin-top: 0;">
                <xsl:text>requs Requirements Specification:</xsl:text>
            </p>
            <p>
                <textarea id="example" style="width: 400px; height: 220px;">start typing...</textarea>
            </p>
        </div>
        <div style="margin-left: 460px;">
            <p style="margin-top: 0;">
                <xsl:text>XML output from requs compiler:</xsl:text>
            </p>
            <pre id="output">...</pre>
        </div>
    </xsl:template>
</xsl:stylesheet>
