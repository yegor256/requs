<?xml version="1.0"?>
<!--
Copyright (c) 2009-2021, Yegor Bugayenko
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met: 1) Redistributions of source code must retain the above
copyright notice, this list of conditions and the following
disclaimer. 2) Redistributions in binary form must reproduce the above
copyright notice, this list of conditions and the following
disclaimer in the documentation and/or other materials provided
with the distribution. 3) Neither the name of the requs.org nor
the names of its contributors may be used to endorse or promote
products derived from this software without specific prior written
permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
OF THE POSSIBILITY OF SUCH DAMAGE.
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
