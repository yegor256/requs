<?xml version="1.0" encoding="UTF-8"?>
<!--
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" version="2.0" exclude-result-prefixes="xs">
  <xsl:output method="xml" cdata-section-elements="svg html"/>
  <xsl:strip-space elements="*"/>
  <xsl:template match="/spec/errors">
    <xsl:copy>
      <xsl:apply-templates select="error"/>
      <xsl:for-each select="//exception/steps[count(step) = 1 and step/signature='fail']">
        <error type="semantic" pos="0">
          <xsl:attribute name="line">
            <xsl:value-of select="step[1]/mentioned/where[1]"/>
          </xsl:attribute>
          <xsl:text>Exception flow of </xsl:text>
          <xsl:value-of select="../../../../../id"/>
          <xsl:text>/</xsl:text>
          <xsl:value-of select="../../../number"/>
          <xsl:text> simply re-throws an exception, it is pointless</xsl:text>
        </error>
      </xsl:for-each>
    </xsl:copy>
  </xsl:template>
  <xsl:template match="node()|@*">
    <xsl:copy>
      <xsl:apply-templates select="node()|@*"/>
    </xsl:copy>
  </xsl:template>
</xsl:stylesheet>
