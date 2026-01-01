<?xml version="1.0" encoding="UTF-8"?>
<!--
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
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
      <xsl:for-each select="//exception[bindings]">
        <error type="semantic" pos="0">
          <xsl:attribute name="line">
            <xsl:value-of select="steps/step/mentioned/where[1]"/>
          </xsl:attribute>
          <xsl:text>exception of step </xsl:text>
          <xsl:value-of select="../../number"/>
          <xsl:text> of method </xsl:text>
          <xsl:value-of select="../../../id"/>
          <xsl:text> has variable declarations (it is prohibited)</xsl:text>
        </error>
      </xsl:for-each>
    </xsl:copy>
  </xsl:template>
  <xsl:template match="exception[bindings]">
    <xsl:copy>
      <xsl:apply-templates select="(node() except bindings)|@*"/>
    </xsl:copy>
  </xsl:template>
</xsl:stylesheet>
