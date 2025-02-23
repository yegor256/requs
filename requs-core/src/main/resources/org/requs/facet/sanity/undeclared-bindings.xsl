<?xml version="1.0"?>
<!--
 * SPDX-FileCopyrightText: Copyright (c) 2009-2025, Yegor Bugayenko
 * SPDX-License-Identifier: MIT
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met: 1) Redistributions of source code must retain the above
 * copyright notice, this list of conditions and the following
 * disclaimer. 2) Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided
 * with the distribution. 3) Neither the name of the requs.org nor
 * the names of its contributors may be used to endorse or promote
 * products derived from this software without specific prior written
 * permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
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
