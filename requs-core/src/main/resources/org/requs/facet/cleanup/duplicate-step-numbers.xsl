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
      <xsl:for-each select="//steps">
        <xsl:variable name="unique" select="count(step[not(number=preceding-sibling::step/number)])"/>
        <xsl:variable name="total" select="count(step)"/>
        <xsl:if test="$unique != $total">
          <error type="syntax" pos="0">
            <xsl:attribute name="line">
              <xsl:value-of select="step[1]/mentioned/where[1]"/>
            </xsl:attribute>
            <xsl:text>there are </xsl:text>
            <xsl:value-of select="$total"/>
            <xsl:text> steps in the flow, while only </xsl:text>
            <xsl:value-of select="$unique"/>
            <xsl:text> of them are unique, obvious duplication of numbers</xsl:text>
          </error>
        </xsl:if>
      </xsl:for-each>
    </xsl:copy>
  </xsl:template>
  <xsl:template match="//steps[count(step[not(number=preceding-sibling::step/number)]) != count(step)]">
    <steps/>
  </xsl:template>
</xsl:stylesheet>
