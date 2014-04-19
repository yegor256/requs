<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    version="2.0" exclude-result-prefixes="xs">
    <xsl:output method="xml"/>
    <xsl:strip-space elements="*" />
    <xsl:template match="/">
        <xsl:processing-instruction name="xml-stylesheet">
            <xsl:text>href="nfrs.xsl" type="text/xsl"</xsl:text>
        </xsl:processing-instruction>
        <nfrs>
            <xsl:apply-templates select="spec/methods/method/nfrs/nfr"/>
        </nfrs>
    </xsl:template>
    <xsl:template match="nfr">
        <xsl:variable name="method" select="../.."/>
        <nfr>
            <xsl:attribute name="id">
                <xsl:value-of select="$method/id"/>
                <xsl:text>/</xsl:text>
                <xsl:value-of select="id"/>
            </xsl:attribute>
            <method>
                <xsl:value-of select="$method/id"/>
            </method>
            <name>
                <xsl:value-of select="id"/>
            </name>
            <description>
                <xsl:value-of select="id"/>
                <xsl:text> must </xsl:text>
                <xsl:for-each select="info/informal">
                    <xsl:if test="position() &gt; 1">
                        <xsl:text>, and must </xsl:text>
                    </xsl:if>
                    <xsl:value-of select="."/>
                </xsl:for-each>
            </description>
        </nfr>
    </xsl:template>
</xsl:stylesheet>
