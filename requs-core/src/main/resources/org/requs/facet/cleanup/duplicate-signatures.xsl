<?xml version="1.0" encoding="UTF-8"?>
<!--
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025, Yegor Bugayenko
 * SPDX-License-Identifier: MIT
-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" version="2.0" exclude-result-prefixes="xs">
  <xsl:output method="xml" cdata-section-elements="svg html"/>
  <xsl:strip-space elements="*"/>
  <xsl:template match="errors">
    <xsl:copy>
      <xsl:apply-templates select="node()|@*"/>
      <xsl:for-each select="//method">
        <xsl:variable name="method" select="."/>
        <xsl:variable name="dups" select="//method[signature=$method/signature and id!=$method/id]"/>
        <xsl:if test="count($dups) &gt; 0">
          <error type="duplicate" pos="0">
            <xsl:attribute name="line">
              <xsl:value-of select="mentioned/where[1]"/>
            </xsl:attribute>
            <xsl:text>method </xsl:text>
            <xsl:value-of select="id"/>
            <xsl:text> has the same signature as </xsl:text>
            <xsl:value-of select="$dups/id" separator=", "/>
            <xsl:text>: "</xsl:text>
            <xsl:value-of select="signature"/>
            <xsl:text>"</xsl:text>
          </error>
        </xsl:if>
      </xsl:for-each>
    </xsl:copy>
  </xsl:template>
  <xsl:template match="methods">
    <xsl:copy>
      <xsl:for-each-group select="method" group-by="signature[1]">
        <xsl:copy-of select="current-group()[1]"/>
      </xsl:for-each-group>
    </xsl:copy>
  </xsl:template>
  <xsl:template match="node()|@*">
    <xsl:copy>
      <xsl:apply-templates select="node()|@*"/>
    </xsl:copy>
  </xsl:template>
</xsl:stylesheet>
