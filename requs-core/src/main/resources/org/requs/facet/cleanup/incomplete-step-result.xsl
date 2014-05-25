<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" version="2.0" exclude-result-prefixes="xs">
    <xsl:output method="xml"/>
    <xsl:strip-space elements="*" />
    <xsl:template match="errors">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
            <xsl:for-each select="//step[result and empty(result/text())]">
                <error type="lost" pos="0">
                    <xsl:attribute name="line">
                        <xsl:value-of select="mentioned/where[1]"/>
                    </xsl:attribute>
                    <xsl:text>step </xsl:text>
                    <xsl:value-of select="number"/>
                    <xsl:text> has broken result declaration</xsl:text>
                </error>
            </xsl:for-each>
        </xsl:copy>
    </xsl:template>
    <xsl:template match="step[result and empty(result/text())]">
        <xsl:copy>
            <xsl:apply-templates select="(node() except result)|@*"/>
        </xsl:copy>
    </xsl:template>
    <xsl:template match="node()|@*">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
        </xsl:copy>
    </xsl:template>
</xsl:stylesheet>
