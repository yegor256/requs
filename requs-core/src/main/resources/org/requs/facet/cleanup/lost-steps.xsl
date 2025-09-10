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
      <xsl:for-each select="//step[exceptions/exception and not(signature) and not(object)]">
        <error type="lost" pos="0">
          <xsl:attribute name="line">
            <xsl:choose>
              <xsl:when test="exceptions/exception/steps/step/mentioned/where">
                <xsl:value-of select="exceptions/exception[1]/steps/step[1]/mentioned/where[1]"/>
              </xsl:when>
              <xsl:otherwise>
                <xsl:text>0:0</xsl:text>
              </xsl:otherwise>
            </xsl:choose>
          </xsl:attribute>
          <xsl:text>step "</xsl:text>
          <xsl:value-of select="number"/>
          <xsl:text>" of method "</xsl:text>
          <xsl:value-of select="../../id"/>
          <xsl:text>" was mentioned but never declared</xsl:text>
        </error>
      </xsl:for-each>
    </xsl:copy>
  </xsl:template>
  <xsl:template match="step[exceptions/exception and not(signature) and not(object)]">
    <xsl:copy>
      <xsl:apply-templates select="(node() except mentioned)|@*"/>
      <signature>"undefined"</signature>
      <object>_self</object>
      <mentioned>
        <where>
          <xsl:choose>
            <xsl:when test="exceptions/exception/steps/step/mentioned/where">
              <xsl:value-of select="exceptions/exception[1]/steps/step[1]/mentioned/where[1]"/>
            </xsl:when>
            <xsl:otherwise>
              <xsl:text>0:0</xsl:text>
            </xsl:otherwise>
          </xsl:choose>
        </where>
      </mentioned>
    </xsl:copy>
  </xsl:template>
</xsl:stylesheet>
