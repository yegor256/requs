<?xml version="1.0"?>
<!--
 * Copyright (c) 2011-2012, ReXSL.com
 * All rights reserved.
 -->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns="http://www.w3.org/1999/xhtml" version="2.0" exclude-result-prefixes="xs">
    <xsl:output method="xml" omit-xml-declaration="yes"/>
    <xsl:include href="/xsl/layout.xsl"/>
    <xsl:template name="head">
        <script type="text/javascript" src="http://code.jquery.com/jquery.min.js">
            <xsl:text> </xsl:text>
            <!-- this is for W3C compliance -->
        </script>
        <script type="text/javascript" src="js/rqdql.js">
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
        <h1>RQDQL Syntax Validation and Parsing</h1>
        <table style="width: 100%;">
            <colgroup>
                <col style="width: 50%;"/>
                <col style="width: 50%;"/>
            </colgroup>
            <thead>
                <tr>
                    <th>RQDQL Syntax</th>
                    <th>Parsing Result</th>
                </tr>
            </thead>
            <tbody>
                <tr>
                    <td><textarea id="example" style="width: 100%; height: 40em;">start typing...</textarea></td>
                    <td id="output">...</td>
                </tr>
            </tbody>
        </table>
    </xsl:template>
</xsl:stylesheet>
