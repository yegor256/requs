<?xml version="1.0"?>
<!--
Copyright (c) 2009-2025, Yegor Bugayenko
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
  <xsl:template match="/spec">
    <xsl:copy>
      <xsl:apply-templates select="node()|@*"/>
      <metrics>
        <metric id="ambiguity.total">
          <xsl:variable name="crud" select="count(//signature[.='creates' or .='reads' or .='updates' or .='deletes' or .= 'fail'])"/>
          <xsl:variable name="informal" select="count(//signature[starts-with(.,'&quot;')])"/>
          <xsl:variable name="total" select="$crud + $informal"/>
          <xsl:choose>
            <xsl:when test="$total = 0">
              <xsl:value-of select="$total"/>
            </xsl:when>
            <xsl:otherwise>
              <xsl:value-of select="format-number($informal div $total, '0.000')"/>
            </xsl:otherwise>
          </xsl:choose>
        </metric>
      </metrics>
    </xsl:copy>
  </xsl:template>
  <xsl:template match="node()|@*">
    <xsl:copy>
      <xsl:apply-templates select="node()|@*"/>
    </xsl:copy>
  </xsl:template>
</xsl:stylesheet>
