<?xml version="1.0" encoding="UTF-8"?>
<!--
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" version="2.0" exclude-result-prefixes="xs">
  <xsl:output method="xml" cdata-section-elements="svg html"/>
  <xsl:strip-space elements="*"/>
  <xsl:template match="errors">
    <xsl:copy>
      <xsl:apply-templates select="node()|@*"/>
      <xsl:for-each select="//method[not(signature) and not(object)]">
        <error type="lost" pos="0">
          <xsl:attribute name="line">
            <xsl:value-of select="mentioned/where"/>
          </xsl:attribute>
          <xsl:text>method </xsl:text>
          <xsl:value-of select="id"/>
          <xsl:text> was mentioned by never declared</xsl:text>
        </error>
      </xsl:for-each>
      <xsl:for-each select="//method[not(signature)]">
        <error type="lost" pos="0">
          <xsl:attribute name="line">
            <xsl:value-of select="mentioned/where"/>
          </xsl:attribute>
          <xsl:text>method </xsl:text>
          <xsl:value-of select="id"/>
          <xsl:text> doesn't have a signature</xsl:text>
        </error>
      </xsl:for-each>
    </xsl:copy>
  </xsl:template>
  <xsl:template match="method[not(signature) and not(object)]">
    <xsl:copy>
      <xsl:apply-templates select="node()|@*"/>
      <signature>"undefined"</signature>
      <object>_self</object>
    </xsl:copy>
  </xsl:template>
  <xsl:template match="method[object and not(signature)]">
    <xsl:copy>
      <xsl:apply-templates select="node()|@*"/>
      <signature>"undefined"</signature>
    </xsl:copy>
  </xsl:template>
  <xsl:template match="node()|@*">
    <xsl:copy>
      <xsl:apply-templates select="node()|@*"/>
    </xsl:copy>
  </xsl:template>
</xsl:stylesheet>
