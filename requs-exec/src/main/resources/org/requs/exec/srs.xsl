<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns="http://www.w3.org/1999/xhtml" version="2.0" exclude-result-prefixes="xs">
    <xsl:output method="xml"/>
    <xsl:strip-space elements="*" />
    <xsl:template match="/">
        <html lang="en">
            <head>
                <meta charset="UTF-8"/>
                <meta name="description" content="SRS"/>
                <meta name="keywords" content="SRS, software requirements specification"/>
                <meta name="author" content="requs"/>
                <meta name="viewport" content="width=device-width, initial-scale=1.0" />
                <style>
                    body { margin: 2em; font-family: Ubuntu; font-size: 16px; }
                    .intro { font-size: 0.9em; color: #777; }
                    .type { margin-top: 2em; }
                    .slots { margin-left: 1em; margin-top: 1em; }
                    .methods { margin-left: 1em; }
                    .method { margin-top: 1em; }
                    .step { margin-left: 1em; }
                    .informal { color: #377; }
                </style>
            </head>
            <body>
                <xsl:apply-templates select="spec"/>
            </body>
        </html>
    </xsl:template>
    <xsl:template match="spec">
        <p class="intro">
            <xsl:text>This document was built on </xsl:text>
            <xsl:value-of select="build/time"/>
            <xsl:text> by </xsl:text>
            <a href="http://www.requs.org">
                <xsl:text>Requs</xsl:text>
            </a>
            <xsl:text> compiler </xsl:text>
            <xsl:value-of select="requs/version"/>
            <xsl:text>/</xsl:text>
            <xsl:value-of select="requs/revision"/>
            <xsl:text> in </xsl:text>
            <xsl:value-of select="build/duration"/>
            <xsl:text>msec.</xsl:text>
        </p>
        <xsl:apply-templates select="metrics"/>
        <xsl:apply-templates select="types/type"/>
    </xsl:template>
    <xsl:template match="metrics">
        <p>
            <xsl:text>Ambiguity: </xsl:text>
            <xsl:value-of select="ambiguity.overall"/>
        </p>
    </xsl:template>
    <xsl:template match="types/type">
        <div class="type">
            <a>
                <xsl:attribute name="name">
                    <xsl:text>#</xsl:text>
                    <xsl:value-of select="name"/>
                </xsl:attribute>
            </a>
            <strong><xsl:value-of select="name"/></strong>
            <xsl:choose>
                <xsl:when test="info/informal">
                    <xsl:text> is </xsl:text>
                    <xsl:apply-templates select="info/informal"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text> is an unknown creature</xsl:text>
                </xsl:otherwise>
            </xsl:choose>
            <xsl:choose>
                <xsl:when test="slots/slot">
                    <xsl:text> that includes:</xsl:text>
                    <div class="slots">
                        <ul>
                            <xsl:apply-templates select="slots/slot"/>
                        </ul>
                    </div>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>.</xsl:text>
                </xsl:otherwise>
            </xsl:choose>
            <xsl:if test="methods/method">
                <xsl:apply-templates select="methods"/>
            </xsl:if>
        </div>
    </xsl:template>
    <xsl:template match="slot">
        <li>
            <xsl:value-of select="name"/>
            <xsl:choose>
                <xsl:when test="arity = 'ANY'">
                    <xsl:text>-s?</xsl:text>
                </xsl:when>
                <xsl:when test="arity = 'MANY'">
                    <xsl:text>-s</xsl:text>
                </xsl:when>
                <xsl:when test="arity = 'OPT'">
                    <xsl:text>-?</xsl:text>
                </xsl:when>
            </xsl:choose>
            <xsl:choose>
                <xsl:when test="type">
                    <xsl:text> as </xsl:text>
                    <xsl:call-template name="type">
                        <xsl:with-param name="type" select="type"/>
                        <xsl:with-param name="label" select="type"/>
                    </xsl:call-template>
                </xsl:when>
            </xsl:choose>
            <xsl:apply-templates select="info/informal"/>
        </li>
    </xsl:template>
    <xsl:template match="methods">
        <div class="methods">
            <xsl:apply-templates select="method"/>
        </div>
    </xsl:template>
    <xsl:template match="method">
        <div class="method">
            <a>
                <xsl:attribute name="name">
                    <xsl:text>#</xsl:text>
                    <xsl:value-of select="id"/>
                </xsl:attribute>
            </a>
            <div>
                <xsl:value-of select="id"/>
                <xsl:text> where </xsl:text>
                <xsl:text>the </xsl:text>
                <xsl:value-of select="args/arg[kind='SELF']/name"/>
                <xsl:text> </xsl:text>
                <em><xsl:value-of select="signature"/></em>
                <xsl:if test="args/arg[kind='RESULT']">
                    <xsl:text> the </xsl:text>
                    <xsl:value-of select="args/arg[kind='RESULT']/name"/>
                </xsl:if>
                <xsl:text>:</xsl:text>
            </div>
            <xsl:apply-templates select="steps/step"/>
        </div>
    </xsl:template>
    <xsl:template match="steps/step">
        <div class="step">
            <div>
                <xsl:value-of select="number"/>
                <xsl:text>. </xsl:text>
                <xsl:text>The </xsl:text>
                <xsl:value-of select="object"/>
                <xsl:text> </xsl:text>
                <em><xsl:value-of select="signature"/></em>
                <xsl:if test="result">
                    <xsl:text> the </xsl:text>
                    <xsl:value-of select="result"/>
                </xsl:if>
                <xsl:if test="args">
                    <xsl:text> using </xsl:text>
                    <xsl:for-each select="args/arg">
                        <xsl:if test="position() != 1">
                            <xsl:text> and </xsl:text>
                        </xsl:if>
                        <xsl:value-of select="."/>
                    </xsl:for-each>
                </xsl:if>
            </div>
        </div>
    </xsl:template>
    <xsl:template match="informal">
        <xsl:text> </xsl:text>
        <xsl:text>"</xsl:text>
        <span class="informal">
            <xsl:value-of select="."/>
        </span>
        <xsl:text>"</xsl:text>
    </xsl:template>
    <xsl:template name="type">
        <xsl:param name="label" />
        <xsl:param name="type" />
        <a>
            <xsl:attribute name="href">
                <xsl:text>#</xsl:text>
                <xsl:value-of select="$type"/>
            </xsl:attribute>
            <xsl:value-of select="$label"/>
        </a>
    </xsl:template>
</xsl:stylesheet>
