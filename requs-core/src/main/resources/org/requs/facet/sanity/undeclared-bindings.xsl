<?xml version="1.0" encoding="UTF-8"?>
<!--
 * SPDX-FileCopyrightText: Copyright (c) 2009-2026 Yegor Bugayenko
 * SPDX-License-Identifier: MIT
-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" version="2.0" exclude-result-prefixes="xs">
  <xsl:output method="xml" cdata-section-elements="svg html"/>
  <xsl:strip-space elements="*"/>
  <xsl:template match="/spec/errors">
    <xsl:copy>
      <xsl:apply-templates select="error"/>
      <xsl:for-each select="//method">
        <xsl:variable name="method" select="."/>
        <xsl:for-each select=".//step">
          <xsl:variable name="step" select="."/>
          <xsl:if test="$step/object and not($method/bindings/binding[name=$step/object])">
            <xsl:call-template name="error">
              <xsl:with-param name="method" select="$method"/>
              <xsl:with-param name="step" select="$step"/>
              <xsl:with-param name="ref" select="$step/object"/>
            </xsl:call-template>
          </xsl:if>
          <xsl:if test="$step/result and not($method/bindings/binding[name=$step/result])">
            <xsl:call-template name="error">
              <xsl:with-param name="method" select="$method"/>
              <xsl:with-param name="step" select="$step"/>
              <xsl:with-param name="ref" select="$step/result"/>
            </xsl:call-template>
          </xsl:if>
          <xsl:for-each select="$step/args/arg">
            <xsl:variable name="arg" select="."/>
            <xsl:if test="not($method/bindings/binding[name=$arg])">
              <xsl:call-template name="error">
                <xsl:with-param name="method" select="$method"/>
                <xsl:with-param name="step" select="$step"/>
                <xsl:with-param name="ref" select="."/>
              </xsl:call-template>
            </xsl:if>
          </xsl:for-each>
        </xsl:for-each>
      </xsl:for-each>
    </xsl:copy>
  </xsl:template>
  <xsl:template name="error">
    <xsl:param name="method"/>
    <xsl:param name="step"/>
    <xsl:param name="ref"/>
    <error type="semantic" pos="0">
      <xsl:attribute name="line">
        <xsl:value-of select="$step/mentioned/where[1]"/>
      </xsl:attribute>
      <xsl:text>"</xsl:text>
      <xsl:value-of select="$ref"/>
      <xsl:text>" is mentioned in step "</xsl:text>
      <xsl:value-of select="$step/number"/>
      <xsl:text>" but was never declared in method "</xsl:text>
      <xsl:value-of select="$method/id"/>
      <xsl:text>"</xsl:text>
    </error>
  </xsl:template>
  <xsl:template match="node()|@*">
    <xsl:copy>
      <xsl:apply-templates select="node()|@*"/>
    </xsl:copy>
  </xsl:template>
</xsl:stylesheet>
