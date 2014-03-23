<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns="http://www.w3.org/1999/xhtml" version="2.0" exclude-result-prefixes="xs">
    <xsl:template match="/">
        <xsl:text disable-output-escaping="yes">&lt;!DOCTYPE html&gt;</xsl:text>
        <xsl:apply-templates select="spec"/>
    </xsl:template>
    <xsl:template match="spec">
        <html lang="en">
            <head>
                <meta charset="UTF-8"/>
                <meta name="description" content="SRS"/>
                <meta name="keywords" content="SRS, software requirements specification"/>
                <meta name="author" content="requs"/>
                <meta name="viewport" content="width=device-width, initial-scale=1.0" />
                <style>
                    body { margin: 2em; font-family: Ubuntu; font-size: 16px; }
                    .type { margin-top: 2em; }
                    .methods { margin-left: 2em; }
                </style>
            </head>
            <body>
                <xsl:apply-templates select="types/type"/>
            </body>
        </html>
    </xsl:template>
    <xsl:template match="types/type">
        <div class="type">
            <xsl:value-of select="name"/>
            <xsl:if test="info/informal">
                <xsl:text> is a </xsl:text>
            </xsl:if>
            <xsl:apply-templates select="methods"/>
        </div>
    </xsl:template>
    <xsl:template match="methods">
        <div class="methods">
        </div>
    </xsl:template>
    <xsl:template match="method">
        <div>
            <div>
                <xsl:value-of select="id"/>
                <xsl:text> where </xsl:text>
                <xsl:text>the </xsl:text>
                <xsl:value-of select="object"/>
                <xsl:text> </xsl:text>
                <xsl:value-of select="signature"/>
                <xsl:text> the </xsl:text>
                <xsl:value-of select="result"/>
                <xsl:text>:</xsl:text>
            </div>
            <xsl:apply-templates select="steps/step"/>
        </div>
    </xsl:template>
</xsl:stylesheet>
