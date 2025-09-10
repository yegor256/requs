<?xml version="1.0" encoding="UTF-8"?>
<!--
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025, Yegor Bugayenko
 * SPDX-License-Identifier: MIT
-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" version="2.0" exclude-result-prefixes="xs">
  <xsl:output method="xml" cdata-section-elements="svg html"/>
  <xsl:strip-space elements="*"/>
  <xsl:template match="node()|@*">
    <xsl:copy>
      <xsl:apply-templates select="node()|@*"/>
    </xsl:copy>
  </xsl:template>
  <xsl:template match="errors">
    <xsl:copy>
      <xsl:apply-templates select="node()|@*"/>
      <xsl:for-each select="//step[count(signature) &gt; 1]">
        <error type="syntax" pos="0">
          <xsl:attribute name="line">
            <xsl:value-of select="mentioned/where[1]"/>
          </xsl:attribute>
          <xsl:text>step </xsl:text>
          <xsl:value-of select="number"/>
          <xsl:text> has </xsl:text>
          <xsl:value-of select="count(signature)"/>
          <xsl:text> signatures</xsl:text>
        </error>
      </xsl:for-each>
    </xsl:copy>
  </xsl:template>
  <xsl:template match="//step[count(signature) &gt; 1]">
    <xsl:copy>
      <xsl:apply-templates select="(node() except signature)|@*"/>
      <signature>
        <xsl:value-of select="signature[1]"/>
      </signature>
    </xsl:copy>
  </xsl:template>
</xsl:stylesheet>
