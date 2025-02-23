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
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:re="http://www.requs.org" xmlns:r="org.requs.facet.uml.Plant" version="2.0" exclude-result-prefixes="xs r re">
  <xsl:import href="uml/functions.xsl"/>
  <xsl:output method="xml" cdata-section-elements="svg html"/>
  <xsl:strip-space elements="*"/>
  <xsl:template match="spec/types/type">
    <xsl:copy>
      <xsl:apply-templates select="(node() except diagrams)|@*"/>
      <xsl:variable name="uml">
        <xsl:text>left to right direction
</xsl:text>
        <xsl:text>hide class circle
</xsl:text>
        <xsl:text>title </xsl:text>
        <xsl:value-of select="name"/>
        <xsl:text>: Class Diagram
</xsl:text>
        <xsl:apply-templates select="." mode="uml"/>
      </xsl:variable>
      <diagrams>
        <xsl:apply-templates select="diagrams/*"/>
        <diagram>
          <uml>
            <xsl:value-of select="$uml"/>
          </uml>
          <svg>
            <xsl:value-of select="r:svg(re:plant($uml))"/>
          </svg>
        </diagram>
      </diagrams>
    </xsl:copy>
  </xsl:template>
  <xsl:template match="type" mode="uml">
    <xsl:variable name="type" select="name"/>
    <xsl:text>class </xsl:text>
    <xsl:value-of select="$type"/>
    <xsl:text> {
</xsl:text>
    <xsl:for-each select="slots/slot[not(type)]">
      <xsl:text>  </xsl:text>
      <xsl:value-of select="name"/>
      <xsl:if test="arity != '1'">
        <xsl:text>[]</xsl:text>
      </xsl:if>
      <xsl:text>
</xsl:text>
    </xsl:for-each>
    <xsl:text>}
</xsl:text>
    <xsl:for-each select="slots/slot[type]">
      <xsl:text>class </xsl:text>
      <xsl:value-of select="type"/>
      <xsl:text>
</xsl:text>
      <xsl:value-of select="$type"/>
      <xsl:text> </xsl:text>
      <xsl:choose>
        <xsl:when test="composition='true'">
          <xsl:text> *--</xsl:text>
        </xsl:when>
        <xsl:otherwise>
          <xsl:text> o--</xsl:text>
        </xsl:otherwise>
      </xsl:choose>
      <xsl:text> </xsl:text>
      <xsl:value-of select="type"/>
      <xsl:text>: </xsl:text>
      <xsl:value-of select="name"/>
      <xsl:text>
</xsl:text>
    </xsl:for-each>
  </xsl:template>
  <xsl:template match="node()|@*">
    <xsl:copy>
      <xsl:apply-templates select="node()|@*"/>
    </xsl:copy>
  </xsl:template>
</xsl:stylesheet>
