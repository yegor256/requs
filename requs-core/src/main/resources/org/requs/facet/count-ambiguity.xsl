<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    version="2.0" exclude-result-prefixes="xs">
    <xsl:output method="xml"/>
    <xsl:strip-space elements="*" />
    <xsl:template match="/spec">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
            <metrics>
                <metric id="overall">
                    <xsl:variable name="crud" select="count(//signature[.='creates' or .='reads' or .='updates' or .='deletes'])"/>
                    <xsl:variable name="informal" select="count(//signature[starts-with(.,'&quot;')])"/>
                    <xsl:variable name="total" select="$crud + $informal"/>
                    <xsl:choose>
                        <xsl:when test="$total = 0">
                            <xsl:value-of select="$total"/>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:value-of select="$informal div $total"/>
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
