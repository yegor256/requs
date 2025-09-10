<?xml version="1.0" encoding="UTF-8"?>
<!--
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025, Yegor Bugayenko
 * SPDX-License-Identifier: MIT
-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:re="http://www.requs.org" version="2.0" exclude-result-prefixes="xs re">
  <xsl:function name="re:plant" as="xs:string">
    <xsl:param name="text"/>
    <xsl:value-of select="concat(             '@startuml&#10;',             'skinparam titleFontSize 13&#10;',             'skinparam titleFontStyle bold&#10;',             'skinparam sequenceTitleFontSize 13&#10;',             'skinparam sequenceTitleFontStyle bold&#10;',             $text,             '&#10;@enduml'         )"/>
  </xsl:function>
  <xsl:function name="re:signature">
    <xsl:param name="text"/>
    <xsl:variable name="max" select="8"/>
    <xsl:variable name="words" select="tokenize(replace($text, '[\n\r\t ]+', ' '), '\s')"/>
    <xsl:for-each select="$words[position() &lt; $max + 1]">
      <xsl:choose>
        <xsl:when test="position() mod 3 = 0">
          <xsl:text>\n</xsl:text>
        </xsl:when>
        <xsl:when test="position() &gt; 1">
          <xsl:text> </xsl:text>
        </xsl:when>
      </xsl:choose>
      <xsl:value-of select="."/>
    </xsl:for-each>
    <xsl:if test="count($words) &gt; $max">
      <xsl:text>...</xsl:text>
    </xsl:if>
  </xsl:function>
  <xsl:template match="node()|@*">
    <xsl:copy>
      <xsl:apply-templates select="node()|@*"/>
    </xsl:copy>
  </xsl:template>
</xsl:stylesheet>
