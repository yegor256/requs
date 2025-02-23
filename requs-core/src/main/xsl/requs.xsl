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
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns="http://www.w3.org/1999/xhtml" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes"/>
  <xsl:template match="/">
    <xsl:text disable-output-escaping="yes">&lt;!DOCTYPE html&gt;</xsl:text>
    <html lang="en-US">
      <head>
        <meta charset="UTF-8"/>
        <meta name="keywords" content="software requirements specification"/>
        <meta name="author" content="requs.org"/>
        <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
        <link rel="icon" type="image/png" href="//img.requs.org/ico-64x64.png"/>
        <style type="text/css">css-included-here</style>
        <title>SRS</title>
      </head>
      <body>
        <div class="container">
          <xsl:apply-templates select="spec"/>
        </div>
      </body>
    </html>
  </xsl:template>
  <xsl:template match="spec">
    <p class="intro">
      <xsl:text>This document was built in </xsl:text>
      <xsl:value-of select="@msec"/>
      <xsl:text> msec on </xsl:text>
      <xsl:value-of select="@time"/>
      <xsl:text> by </xsl:text>
      <a href="http://www.requs.org">
        <xsl:text>Requs</xsl:text>
      </a>
      <xsl:text> compiler </xsl:text>
      <xsl:value-of select="requs/version"/>
      <xsl:text>/</xsl:text>
      <xsl:value-of select="requs/revision"/>
      <xsl:text>.</xsl:text>
    </p>
    <xsl:if test="errors[error]">
      <h1>
        <xsl:text>Errors</xsl:text>
      </h1>
      <xsl:apply-templates select="errors/error"/>
    </xsl:if>
    <h1>
      <xsl:text>Scope Definition</xsl:text>
    </h1>
    <xsl:apply-templates select="." mode="scope"/>
    <xsl:if test="acronyms[acronym]">
      <h1>
        <xsl:text>Definitions/Acronyms</xsl:text>
      </h1>
      <xsl:apply-templates select="acronyms/acronym"/>
    </xsl:if>
    <h1>
      <xsl:text>Types and Methods</xsl:text>
    </h1>
    <xsl:apply-templates select="types/type"/>
    <xsl:if test="pages[page]">
      <h1>
        <xsl:text>Markdown Pages</xsl:text>
      </h1>
      <xsl:apply-templates select="pages/page"/>
    </xsl:if>
    <xsl:if test="tbds[tbd]">
      <xsl:apply-templates select="tbds"/>
    </xsl:if>
    <xsl:if test="metrics[metric]">
      <h1>
        <xsl:text>Metrics</xsl:text>
      </h1>
      <xsl:apply-templates select="metrics/metric"/>
    </xsl:if>
  </xsl:template>
  <xsl:template match="spec" mode="scope">
    <p>
      <xsl:value-of select="count(types/type)"/>
      <xsl:text> type(s): </xsl:text>
      <xsl:for-each select="types/type">
        <xsl:if test="position() &gt; 1">
          <xsl:text>, </xsl:text>
        </xsl:if>
        <a href="#{name}">
          <xsl:value-of select="name"/>
        </a>
      </xsl:for-each>
    </p>
    <p>
      <xsl:value-of select="count(methods/method)"/>
      <xsl:text> Use Case(s): </xsl:text>
      <xsl:for-each select="methods/method">
        <xsl:if test="position() &gt; 1">
          <xsl:text>, </xsl:text>
        </xsl:if>
        <a href="#{id}">
          <xsl:value-of select="id"/>
        </a>
      </xsl:for-each>
    </p>
    <p>
      <xsl:value-of select="count(//step[signature='creates' or signature='reads' or signature='updates' or signature='deletes'])"/>
      <xsl:text> CRUD operator(s)</xsl:text>
    </p>
    <p>
      <xsl:value-of select="count(//slot)"/>
      <xsl:text> slot(s)</xsl:text>
    </p>
  </xsl:template>
  <xsl:template match="metrics/metric">
    <p>
      <xsl:value-of select="@id"/>
      <xsl:text> = </xsl:text>
      <xsl:value-of select="."/>
    </p>
  </xsl:template>
  <xsl:template match="errors/error">
    <p>
      <xsl:text>[</xsl:text>
      <xsl:value-of select="@line"/>
      <xsl:text>:</xsl:text>
      <xsl:value-of select="@pos"/>
      <xsl:text>] </xsl:text>
      <xsl:value-of select="."/>
    </p>
  </xsl:template>
  <xsl:template match="acronyms/acronym">
    <p>
      <strong>
        <xsl:value-of select="name"/>
      </strong>
      <xsl:text> means </xsl:text>
      <xsl:apply-templates select="info/informal"/>
    </p>
  </xsl:template>
  <xsl:template match="page">
    <h2>
      <xsl:value-of select="title"/>
    </h2>
    <xsl:value-of select="html" disable-output-escaping="yes"/>
  </xsl:template>
  <xsl:template match="types/type">
    <div class="type" id="{name}">
      <xsl:if test="actor='true'">
        <strong>
          <xsl:value-of select="name"/>
        </strong>
        <xsl:text> is an actor. </xsl:text>
      </xsl:if>
      <strong>
        <xsl:value-of select="name"/>
      </strong>
      <xsl:text> is </xsl:text>
      <xsl:if test="parents/type">
        <xsl:for-each select="parents/type">
          <xsl:if test="position() &gt; 1">
            <xsl:text> and </xsl:text>
          </xsl:if>
          <a href="#{.}">
            <xsl:value-of select="."/>
          </a>
        </xsl:for-each>
      </xsl:if>
      <xsl:choose>
        <xsl:when test="info/informal">
          <xsl:apply-templates select="info/informal"/>
        </xsl:when>
        <xsl:when test="not(parents/type)">
          <span class="warning">
            <xsl:text>an unknown creature</xsl:text>
          </span>
        </xsl:when>
      </xsl:choose>
      <xsl:choose>
        <xsl:when test="slots/slot">
          <xsl:text> that includes:</xsl:text>
          <div class="slots">
            <ul>
              <xsl:apply-templates select="slots/slot"/>
            </ul>
          </div>
          <xsl:apply-templates select="diagrams/diagram"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:text>.</xsl:text>
        </xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates select="/spec/methods/method[bindings/binding[name='_self' and type=current()/name]]"/>
    </div>
  </xsl:template>
  <xsl:template match="slot">
    <li>
      <xsl:value-of select="name"/>
      <xsl:choose>
        <xsl:when test="arity = '0..*'">
          <xsl:text>-s?</xsl:text>
        </xsl:when>
        <xsl:when test="arity = '1..*'">
          <xsl:text>-s</xsl:text>
        </xsl:when>
      </xsl:choose>
      <xsl:if test="type">
        <xsl:text> as </xsl:text>
        <a href="#{type}">
          <xsl:value-of select="type"/>
        </a>
        <xsl:if test="composition='true'">
          <xsl:text>!</xsl:text>
        </xsl:if>
      </xsl:if>
      <xsl:apply-templates select="info/informal"/>
    </li>
  </xsl:template>
  <xsl:template match="method">
    <div class="method">
      <div id="{id}">
        <strong>
          <xsl:value-of select="id"/>
        </strong>
        <xsl:text> where </xsl:text>
        <xsl:call-template name="signature">
          <xsl:with-param name="bindings" select="bindings"/>
          <xsl:with-param name="home" select="."/>
          <xsl:with-param name="typed" select="'true'"/>
        </xsl:call-template>
        <xsl:text>:</xsl:text>
        <xsl:if test="@seal">
          <span class="label seal">
            <xsl:value-of select="@seal"/>
          </span>
        </xsl:if>
        <xsl:apply-templates select="attributes/attribute"/>
      </div>
      <div class="steps">
        <xsl:apply-templates select="info/informal"/>
        <xsl:apply-templates select="steps"/>
      </div>
      <div class="nfrs">
        <xsl:apply-templates select="nfrs/nfr"/>
      </div>
      <xsl:if test="steps/step">
        <xsl:apply-templates select="diagrams/diagram"/>
      </xsl:if>
    </div>
  </xsl:template>
  <xsl:template match="attribute">
    <span>
      <xsl:attribute name="class">
        <xsl:text>label </xsl:text>
        <xsl:choose>
          <xsl:when test="@seal = ../../@seal">
            <xsl:text>sealed</xsl:text>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>attribute</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:attribute>
      <xsl:value-of select="."/>
    </span>
  </xsl:template>
  <xsl:template match="steps">
    <div class="steps">
      <xsl:apply-templates select="step"/>
    </div>
  </xsl:template>
  <xsl:template match="step">
    <div class="step">
      <xsl:value-of select="number"/>
      <xsl:text>. </xsl:text>
      <xsl:call-template name="signature">
        <xsl:with-param name="bindings" select="../../bindings"/>
        <xsl:with-param name="home" select="."/>
      </xsl:call-template>
      <xsl:apply-templates select="info/informal"/>
      <xsl:apply-templates select="exceptions/exception"/>
    </div>
  </xsl:template>
  <xsl:template match="exception">
    <div class="exception">
      <xsl:text>if/when "</xsl:text>
      <xsl:value-of select="when"/>
      <xsl:text>":</xsl:text>
      <xsl:apply-templates select="steps"/>
    </div>
  </xsl:template>
  <xsl:template match="nfr">
    <div class="nfr">
      <xsl:value-of select="id"/>
      <xsl:text> must </xsl:text>
      <xsl:apply-templates select="info/informal"/>
    </div>
  </xsl:template>
  <xsl:template match="informal">
    <xsl:text> </xsl:text>
    <span class="informal">
      <xsl:text>"</xsl:text>
      <xsl:value-of select="."/>
      <xsl:text>"</xsl:text>
    </span>
    <xsl:text> </xsl:text>
  </xsl:template>
  <xsl:template name="signature">
    <xsl:param name="bindings"/>
    <xsl:param name="home"/>
    <xsl:param name="typed" select="'false'"/>
    <xsl:call-template name="ref">
      <xsl:with-param name="bindings" select="$bindings"/>
      <xsl:with-param name="name" select="$home/object"/>
      <xsl:with-param name="typed" select="$typed"/>
    </xsl:call-template>
    <xsl:text> </xsl:text>
    <xsl:variable name="uc" select="/spec/methods/method[signature=$home/signature]/id"/>
    <xsl:choose>
      <xsl:when test="$home/signature='creates' or $home/signature='reads' or $home/signature='updates' or $home/signature='deletes'">
        <span class="crud">
          <xsl:value-of select="$home/signature"/>
        </span>
      </xsl:when>
      <xsl:when test="$home/signature='fail'">
        <span class="fail">
          <xsl:text>Fail as</xsl:text>
        </span>
      </xsl:when>
      <xsl:when test="$uc">
        <a href="#{$uc}">
          <xsl:value-of select="$home/signature"/>
        </a>
      </xsl:when>
      <xsl:otherwise>
        <span class="warning">
          <xsl:value-of select="$home/signature"/>
        </span>
      </xsl:otherwise>
    </xsl:choose>
    <xsl:text> </xsl:text>
    <xsl:if test="$home/result">
      <xsl:call-template name="ref">
        <xsl:with-param name="bindings" select="$bindings"/>
        <xsl:with-param name="name" select="$home/result"/>
        <xsl:with-param name="typed" select="$typed"/>
      </xsl:call-template>
    </xsl:if>
    <xsl:if test="$home/args/arg">
      <xsl:text> using </xsl:text>
      <xsl:for-each select="$home/args/arg">
        <xsl:if test="position() &gt; 1">
          <xsl:text> and </xsl:text>
        </xsl:if>
        <xsl:call-template name="ref">
          <xsl:with-param name="bindings" select="$bindings"/>
          <xsl:with-param name="name" select="."/>
          <xsl:with-param name="typed" select="$typed"/>
        </xsl:call-template>
      </xsl:for-each>
    </xsl:if>
  </xsl:template>
  <xsl:template name="ref">
    <xsl:param name="bindings"/>
    <xsl:param name="name"/>
    <xsl:param name="typed" select="'false'"/>
    <xsl:variable name="type" select="$bindings/binding[name=$name]/type"/>
    <a href="#{$type}">
      <xsl:choose>
        <xsl:when test="contains($name,'_')">
          <xsl:value-of select="$type"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:choose>
            <xsl:when test="$typed = 'true'">
              <xsl:value-of select="$type"/>
              <xsl:text> (a</xsl:text>
              <xsl:if test="substring($name, 1, 1) = 'a' or substring($name, 1, 1) = 'i'">
                <xsl:text>n</xsl:text>
              </xsl:if>
              <xsl:text> </xsl:text>
              <xsl:value-of select="$name"/>
              <xsl:text>)</xsl:text>
            </xsl:when>
            <xsl:otherwise>
              <xsl:value-of select="$name"/>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:otherwise>
      </xsl:choose>
    </a>
  </xsl:template>
  <xsl:template match="tbds">
    <h1>
      <xsl:text>TBDs</xsl:text>
    </h1>
    <table>
      <thead>
        <tr>
          <th>ID</th>
          <th>Subject</th>
          <th>Description</th>
        </tr>
      </thead>
      <tbody>
        <xsl:apply-templates select="tbd"/>
      </tbody>
    </table>
  </xsl:template>
  <xsl:template match="tbd">
    <tr>
      <td>
        <xsl:value-of select="@id"/>
      </td>
      <td>
        <xsl:value-of select="subject"/>
      </td>
      <td>
        <xsl:value-of select="description"/>
      </td>
    </tr>
  </xsl:template>
  <xsl:template match="diagram">
    <div>
      <div class="uml">
        <xsl:value-of select="svg" disable-output-escaping="yes"/>
      </div>
    </div>
  </xsl:template>
</xsl:stylesheet>
