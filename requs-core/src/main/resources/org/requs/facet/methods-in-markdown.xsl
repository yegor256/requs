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
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions" xmlns:r="org.requs.facet.XsltFuncs" version="2.0" exclude-result-prefixes="xs fn r">
  <xsl:output method="xml" cdata-section-elements="svg html"/>
  <xsl:strip-space elements="*"/>
  <xsl:template match="/spec">
    <xsl:copy>
      <xsl:apply-templates select="node()|@*"/>
    </xsl:copy>
  </xsl:template>
  <xsl:template match="method">
    <xsl:variable name="md">
      <x>
        <xsl:apply-templates select="." mode="x"/>
      </x>
    </xsl:variable>
    <xsl:copy>
      <xsl:apply-templates select="node()|@*"/>
      <xsl:variable name="markdown" select="r:print($md)"/>
      <markdown>
        <xsl:value-of select="$markdown"/>
      </markdown>
      <html>
        <xsl:value-of select="r:html($markdown)"/>
      </html>
    </xsl:copy>
  </xsl:template>
  <xsl:template match="method" mode="x">
    <xsl:text>The following table describes all technical details of Use Case `</xsl:text>
    <xsl:value-of select="id"/>
    <xsl:text>`:

</xsl:text>
    <div>
      <table>
        <thead>
          <tr>
            <th>
              <xsl:text>Property</xsl:text>
            </th>
            <th>
              <xsl:text>Details</xsl:text>
            </th>
          </tr>
        </thead>
        <tbody>
          <tr>
            <td>
              <xsl:text>ID</xsl:text>
            </td>
            <td>
              <xsl:value-of select="id"/>
            </td>
          </tr>
          <tr>
            <td>
              <xsl:text>Signature</xsl:text>
            </td>
            <td>
              <xsl:call-template name="signature">
                <xsl:with-param name="home" select="."/>
              </xsl:call-template>
            </td>
          </tr>
          <tr>
            <td>
              <xsl:text>Primary</xsl:text>
            </td>
            <td>
              <xsl:value-of select="bindings/binding[name='_self']/type"/>
            </td>
          </tr>
          <tr>
            <td>
              <xsl:text>Actors</xsl:text>
            </td>
            <td>
              <xsl:for-each select="bindings/binding[name!='_self']">
                <xsl:if test="position() != 1">
                  <xsl:text>; </xsl:text>
                </xsl:if>
                <code>
                  <xsl:value-of select="name"/>
                </code>
                <xsl:text> as </xsl:text>
                <xsl:value-of select="type"/>
              </xsl:for-each>
            </td>
          </tr>
          <xsl:if test="info/informal">
            <tr>
              <td>
                <xsl:text>Brief</xsl:text>
              </td>
              <td>
                <xsl:for-each select="info/informal">
                  <xsl:if test="position() != 1">
                    <br/>
                  </xsl:if>
                  <xsl:apply-templates select="." mode="x"/>
                </xsl:for-each>
              </td>
            </tr>
          </xsl:if>
          <xsl:if test="steps/step">
            <tr>
              <td>
                <xsl:text>Success Flow</xsl:text>
              </td>
              <td>
                <xsl:apply-templates select="steps" mode="x"/>
              </td>
            </tr>
          </xsl:if>
          <xsl:if test="nfrs/nfr">
            <tr>
              <td>
                <xsl:text>NFRs</xsl:text>
              </td>
              <td>
                <xsl:apply-templates select="nfrs" mode="x"/>
              </td>
            </tr>
          </xsl:if>
        </tbody>
      </table>
    </div>
    <xsl:text>

Actors taking participation in the Use Case have the following properties:

</xsl:text>
    <div>
      <table>
        <thead>
          <tr>
            <th>
              <xsl:text>Actor</xsl:text>
            </th>
            <th>
              <xsl:text>Properties</xsl:text>
            </th>
          </tr>
        </thead>
        <tbody>
          <xsl:for-each-group select="bindings/binding" group-by="type">
            <xsl:variable name="type" select="fn:current-grouping-key()"/>
            <tr>
              <td>
                <xsl:value-of select="$type"/>
              </td>
              <td>
                <xsl:apply-templates select="/spec/types/type[name=$type]" mode="x"/>
              </td>
            </tr>
          </xsl:for-each-group>
        </tbody>
      </table>
    </div>
  </xsl:template>
  <xsl:template match="steps" mode="x">
    <xsl:for-each select="step">
      <xsl:if test="position() != 1">
        <br/>
      </xsl:if>
      <xsl:apply-templates select="." mode="x"/>
    </xsl:for-each>
  </xsl:template>
  <xsl:template match="step" mode="x">
    <xsl:value-of select="number"/>
    <xsl:text>. </xsl:text>
    <xsl:call-template name="signature">
      <xsl:with-param name="home" select="."/>
    </xsl:call-template>
  </xsl:template>
  <xsl:template match="informal" mode="x">
    <xsl:text>"</xsl:text>
    <xsl:value-of select="fn:replace(., '[&#10; ]+', ' ')"/>
    <xsl:text>"</xsl:text>
  </xsl:template>
  <xsl:template name="signature">
    <xsl:param name="home"/>
    <code>
      <xsl:value-of select="$home/object"/>
    </code>
    <xsl:text> </xsl:text>
    <xsl:value-of select="$home/signature"/>
    <xsl:if test="$home/result">
      <xsl:text> </xsl:text>
      <code>
        <xsl:value-of select="$home/result"/>
      </code>
    </xsl:if>
    <xsl:if test="$home/args/arg">
      <xsl:text> using </xsl:text>
      <xsl:for-each select="$home/args/arg">
        <xsl:if test="position() &gt; 1">
          <xsl:text> and </xsl:text>
        </xsl:if>
        <code>
          <xsl:value-of select="."/>
        </code>
      </xsl:for-each>
    </xsl:if>
  </xsl:template>
  <xsl:template match="type" mode="x">
    <xsl:for-each select="info/informal">
      <xsl:if test="position() &gt; 1">
        <br/>
      </xsl:if>
      <xsl:apply-templates select="." mode="x"/>
    </xsl:for-each>
    <xsl:if test="slots/slot">
      <ul>
        <xsl:for-each select="slots/slot">
          <li>
            <code>
              <xsl:value-of select="name"/>
            </code>
            <xsl:text>: </xsl:text>
            <xsl:value-of select="type"/>
            <xsl:apply-templates select="info" mode="x"/>
          </li>
        </xsl:for-each>
      </ul>
    </xsl:if>
  </xsl:template>
  <xsl:template match="nfrs" mode="x">
    <xsl:for-each select="nfr">
      <xsl:if test="position() != 1">
        <br/>
      </xsl:if>
      <xsl:apply-templates select="." mode="x"/>
    </xsl:for-each>
  </xsl:template>
  <xsl:template match="nfr" mode="x">
    <xsl:value-of select="id"/>
    <xsl:text> must </xsl:text>
    <xsl:apply-templates select="info" mode="x"/>
  </xsl:template>
  <xsl:template match="info" mode="x">
    <xsl:if test="informal">
      <xsl:text> </xsl:text>
      <xsl:for-each select="informal">
        <xsl:if test="position() &gt; 1">
          <xsl:text> and </xsl:text>
        </xsl:if>
        <xsl:apply-templates select="." mode="x"/>
      </xsl:for-each>
    </xsl:if>
  </xsl:template>
  <xsl:template match="node()|@*">
    <xsl:copy>
      <xsl:apply-templates select="node()|@*"/>
    </xsl:copy>
  </xsl:template>
</xsl:stylesheet>
