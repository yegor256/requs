<?xml version="1.0"?>
<!--
 * Copyright (c) 2009-2014, requs.org
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met: 1) Redistributions of source code must retain the above
 * copyright notice, this list of conditions and the following
 * disclaimer. 2) Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided
 * with the distribution. 3) Neither the name of the requs.org nor
 * the names of its contributors may be used to endorse or promote
 * products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 -->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns="http://www.w3.org/1999/xhtml" version="2.0" exclude-result-prefixes="xs">
    <xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>
    <xsl:include href="/xsl/layout.xsl"/>
    <xsl:template name="head">
        <script type="text/javascript" src="http://code.jquery.com/jquery-2.0.0.js">
            <xsl:text> </xsl:text>
            <!-- this is for W3C compliance -->
        </script>
        <script type="text/javascript" src="/js/demo.js">
            <xsl:text> </xsl:text>
            <!-- this is for W3C compliance -->
        </script>
        <title>
            <xsl:text>requs</xsl:text>
        </title>
    </xsl:template>
    <xsl:template name="content">
        <p>
            <img alt="logo" style="width: 192px; height: 64px;">
                <xsl:attribute name="src">
                    <xsl:text>http://img.requs.org/logo-384x128.png</xsl:text>
                </xsl:attribute>
            </img>
        </p>
        <p>
            <a href="http://www.requs.org/syntax.html">
                <xsl:text>syntax explained</xsl:text>
            </a>
        </p>
        <table style="width:100%;table-layout:fixed;">
            <thead>
                <tr>
                    <th><xsl:text>Requirements</xsl:text></th>
                    <th style="width: 2em;"><xsl:text> </xsl:text></th>
                    <th><xsl:text>XML Output</xsl:text></th>
                </tr>
            </thead>
            <tbody>
                <tr>
                    <td class="half"><textarea class="box" id="example">start typing...</textarea></td>
                    <td><span style="color:green;display:none;" id="arrow"><xsl:text>&#x21e2;</xsl:text></span></td>
                    <td class="half"><pre class="box" id="output">...</pre></td>
                </tr>
            </tbody>
        </table>
    </xsl:template>
</xsl:stylesheet>
