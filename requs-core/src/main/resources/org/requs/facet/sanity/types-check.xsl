<?xml version="1.0" encoding="UTF-8"?>
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
