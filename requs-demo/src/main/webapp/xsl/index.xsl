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
    <xsl:template match="page" mode="head">
        <script type="text/javascript" src="//code.jquery.com/jquery-2.0.0.js">
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
    <xsl:template match="page" mode="body">
        <table>
            <thead>
                <tr>
                    <th class="left">
                        <a href="http://www.requs.org/syntax.html">
                            <img alt="logo" style="width: 96px; height: 32px;" src="//img.requs.org/logo-384x128.png"/>
                        </a>
                        <span style="color:green;display:none;" id="arrow">
                            <xsl:text>loading...</xsl:text>
                        </span>
                    </th>
                    <th class="right">
                        <xsl:apply-templates select="version"/>
                    </th>
                </tr>
            </thead>
            <tbody>
                <tr>
                    <td class="left">
                        <textarea class="box" id="example">
                            <xsl:text>User is "a human being".</xsl:text>
                        </textarea>
                    </td>
                    <td class="right">
                        <iframe class="box" id="srs">
                            <xsl:text>...</xsl:text>
                        </iframe>
                    </td>
                </tr>
                <tr class="separator">
                    <td colspan="2" style="text-align:center">
                        <xsl:text>...</xsl:text>
                    </td>
                </tr>
                <tr id="xml">
                    <td colspan="2">
                        <pre class="box" id="output">
                            <xsl:text>...</xsl:text>
                        </pre>
                    </td>
                </tr>
            </tbody>
        </table>
    </xsl:template>
    <xsl:template match="version">
        <div>
            <xsl:text>made by </xsl:text>
            <a href="http://www.teamed.io">
                <xsl:text>teamed.io</xsl:text>
            </a>
        </div>
        <div>
            <span><xsl:value-of select="name"/></span>
            <span>
                <a href="https://github.com/teamed/requs/commit/{revision}">
                    <xsl:value-of select="revision"/>
                </a>
            </span>
            <span>
                <xsl:call-template name="millis">
                    <xsl:with-param name="millis" select="/page/millis"/>
                </xsl:call-template>
            </span>
        </div>
    </xsl:template>
    <xsl:template name="millis">
        <xsl:param name="millis" as="xs:integer"/>
        <xsl:choose>
            <xsl:when test="$millis &gt; 1000">
                <xsl:value-of select="format-number($millis div 1000, '0.0')"/>
                <xsl:text>s</xsl:text>
            </xsl:when>
            <xsl:otherwise>
                <xsl:value-of select="format-number($millis, '#')"/>
                <xsl:text>ms</xsl:text>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>
</xsl:stylesheet>
