<?xml version="1.0"?>
<!--
Copyright (c) 2009-2017, requs.org
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
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:re="http://www.requs.org" version="2.0" exclude-result-prefixes="xs re">
  <xsl:function name="re:plant" as="xs:string">
    <xsl:param name="text"/>
    <xsl:value-of select="concat(             '@startuml&#10;',             'skinparam titleFontSize 13&#10;',             'skinparam titleFontStyle bold&#10;',             'skinparam sequenceTitleFontSize 13&#10;',             'skinparam sequenceTitleFontStyle bold&#10;',             $text,             '&#10;@enduml'         )"/>
  </xsl:function>
  <xsl:function name="re:signature">
    <xsl:param name="text"/>
    <xsl:variable name="max" select="8"/>
    <xsl:variable name="words" select="tokenize(replace($text, '[\n\r\t ]+', ' '), '\s')"/>
    <xsl:for-each select="$words[position() &lt; $max + 1]">
      <xsl:choose>
        <xsl:when test="position() mod 3 = 0">
          <xsl:text>\n</xsl:text>
        </xsl:when>
        <xsl:when test="position() &gt; 1">
          <xsl:text> </xsl:text>
        </xsl:when>
      </xsl:choose>
      <xsl:value-of select="."/>
    </xsl:for-each>
    <xsl:if test="count($words) &gt; $max">
      <xsl:text>...</xsl:text>
    </xsl:if>
  </xsl:function>
  <xsl:template match="node()|@*">
    <xsl:copy>
      <xsl:apply-templates select="node()|@*"/>
    </xsl:copy>
  </xsl:template>
</xsl:stylesheet>
