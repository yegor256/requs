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
      <xsl:for-each select="/spec/types/type/slots/slot[type]">
        <xsl:variable name="slot" select="."/>
        <xsl:if test="/spec[not(types/type/name=$slot/type)]">
          <error type="seal" pos="0">
            <xsl:attribute name="line">
              <xsl:value-of select="$slot/mentioned/where[1]"/>
            </xsl:attribute>
            <xsl:text>Slot "</xsl:text>
            <xsl:value-of select="$slot/name"/>
            <xsl:text>" of type "</xsl:text>
            <xsl:value-of select="$slot/../../name"/>
            <xsl:text>" refers to a non-existing type "</xsl:text>
            <xsl:value-of select="$slot/type"/>
            <xsl:text>"</xsl:text>
          </error>
        </xsl:if>
      </xsl:for-each>
      <xsl:for-each select="/spec/methods/method/bindings/binding">
        <xsl:variable name="binding" select="."/>
        <xsl:if test="/spec/types[not(type/name=$binding/type)]">
          <error type="seal" pos="0">
            <xsl:attribute name="line">
              <xsl:value-of select="$binding/../../mentioned/where[1]"/>
            </xsl:attribute>
            <xsl:text>Use case "</xsl:text>
            <xsl:value-of select="$binding/../../id"/>
            <xsl:text>" refers to a non-existing type "</xsl:text>
            <xsl:value-of select="$binding/type"/>
            <xsl:text>"</xsl:text>
          </error>
        </xsl:if>
      </xsl:for-each>
      <xsl:for-each select="/spec/types/type/parents/type">
        <xsl:variable name="type" select="."/>
        <xsl:if test="/spec[not(types/type/name=$type)]">
          <error type="seal" pos="0">
            <xsl:attribute name="line">
              <xsl:value-of select="$type/../../mentioned/where[1]"/>
            </xsl:attribute>
            <xsl:text>Parent of type "</xsl:text>
            <xsl:value-of select="$type/../../name"/>
            <xsl:text>" refers to a non-existing type "</xsl:text>
            <xsl:value-of select="$type"/>
            <xsl:text>"</xsl:text>
          </error>
        </xsl:if>
      </xsl:for-each>
    </xsl:copy>
  </xsl:template>
  <xsl:template match="node()|@*">
    <xsl:copy>
      <xsl:apply-templates select="node()|@*"/>
    </xsl:copy>
  </xsl:template>
</xsl:stylesheet>
